using UnityEngine;
using System.Collections;

namespace Pathfinding {
	/// <summary>
	/// Base class for all graphs
	/// </summary>
	public class NavGraph {
		
		/** See NavGraph.guid. This variable is not used.
		 */
		public System.Guid _guid = System.Guid.NewGuid ();
		/// <summary>
		/// See <see cref="NavGraph.guid"/> used to store the guid value
		/// </summary>
		
		/** See NavGraph.guid, used to store the guid value
		 */
		public byte[] _sguid;
		
		
		/** Reference to the AstarPath object in the scene.
		 * Might not be entirely safe to use, it's better to use AstarPath.active
		 */
		public AstarPath active;
		
		/** Used as an ID of the graph, considered to be unique.
		 */
		public System.Guid guid {
			get {
				if (_sguid == null || _sguid.Length != 16) {
					_sguid = System.Guid.NewGuid ().ToByteArray ();
				}
				return new System.Guid (_sguid);
			}
			set {
				_sguid = value.ToByteArray ();
			}
		}
		
		/// <summary>
		/// Is the graph open in the editor
		/// </summary>
		public bool open;
		
#if UNITY_EDITOR
		public bool infoScreenOpen;
#endif
		
		/// <summary>
		/// All nodes this graph contains. This can be iterated to search for a specific node.
		/// This should be set if the graph does contain any nodes
		/// </summary>
		public Node[] nodes;
		
		//public int startIndex;
		//public int endIndex;
		
		//public ModifierHolder sourceModifier;
		
		/*public virtual int GetGraphType () {
			return -1;
		}*/
		
		/// <summary>
		/// A matrix for translating/rotating/scaling the graph. Not all graph generators supports this though.
		/// </summary>
		public Matrix4x4 matrix;
		
		/// <summary>
		/// Creates a number of nodes with the correct type for the graph.
		/// </summary>
		/// <remarks>Called by graph generators and when deserializing a graph with nodes.
		/// Override this function if you do not use the default <see cref="Node"/> class.</remarks>
		/// <param name="number">
		/// A <see cref="System.Int32"/>
		/// </param>
		/// <returns>
		/// A <see cref="Node[]"/>
		/// </returns>
		public virtual Node[] CreateNodes (int number) {
			Node[] tmp = new Node[number];
			for (int i=0;i<number;i++) {
				tmp[i] = new Node ();
			}
			return tmp;
		}
		
		/// <summary>
		/// Relocates the nodes in this graph.
		/// </summary>
		/// <remarks>Assumes the nodes are translated using the "oldMatrix", then translates them according to the "newMatrix".
		/// The "oldMatrix" is not required by all implementations of this function though (e.g the NavMesh generator).</remarks>
		/// <param name="oldMatrix">
		/// A <see cref="Matrix4x4"/>
		/// </param>
		/// <param name="newMatrix">
		/// A <see cref="Matrix4x4"/>
		/// </param>
		public virtual void RelocateNodes (Matrix4x4 oldMatrix, Matrix4x4 newMatrix) {
			
			if (nodes == null || nodes.Length == 0) {
				return;
			}
			
			Matrix4x4 inv = oldMatrix.inverse;
			
			//@ToDo Could the matrixes be merged to one?
			for (int i=0;i<nodes.Length;i++) {
				Vector3 tmp = inv.MultiplyPoint3x4 ((Vector3)nodes[i].position);
				nodes[i].position = (Int3)newMatrix.MultiplyPoint3x4 (tmp);
			}
		}
		
		/// <summary>
		/// Returns the nerest node to a position using the default <see cref="NNConstraint">constraint</see>.
		/// </summary>
		/// <param name="position">
		/// A <see cref="Vector3"/>
		/// </param>
		/// <returns>
		/// A <see cref="NNInfo"/>
		/// </returns>
		public NNInfo GetNearest (Vector3 position) {
			return GetNearest (position, NNConstraint.None);
		}
		
		/** Returns the nearest node to a position using the specified NNConstraint.
		  * \param position The position to try to find a close node to
		  * \param hint Can be passed to enable some graph generators to find the nearest node faster.
		  * \param constraint Can for example tell the function to try to return a walkable node. If you do not get a good node back, consider calling GetNearestForce. */
		public virtual NNInfo GetNearest (Vector3 position, NNConstraint constraint, Node hint = null) {
			//Debug.LogError ("This function (GetNearest) is not implemented in the navigation graph generator : Type "+this.GetType ().Name);
			
			if (nodes == null) {
				return new NNInfo ();
			}
			
			float minDist = float.PositiveInfinity;
			Node minNode = null;
			
			float minConstDist = float.PositiveInfinity;
			Node minConstNode = null;
			
			for (int i=0;i<nodes.Length;i++) {
				
				Node node = nodes[i];
				float dist = (position-(Vector3)node.position).sqrMagnitude;
				
				if (dist < minDist) {
					minDist = dist;
					minNode = node;
				}
				
				if (constraint.Suitable (node) && dist < minConstDist) {
					minConstDist = dist;
					minConstNode = node;
				}
			}
			
			NNInfo nnInfo = new NNInfo (minNode);
			
			nnInfo.constrainedNode = minConstNode;
			
			if (minConstNode != null) {
				nnInfo.constClampedPosition = minConstNode.position;
			} else if (minNode != null) {
				nnInfo.constrainedNode = minNode;
				nnInfo.constClampedPosition = minNode.position;
			}
			
			return nnInfo;
		}
		
		/// <summary>
		/// Returns the nearest node to a position using the specified <see cref="NNConstraint">constraint</see>.
		/// </summary>
		/// <param name="position">
		/// A <see cref="Vector3"/>
		/// </param>
		/// <param name="constraint">
		/// A <see cref="NNConstraint"/>
		/// </param>
		/// <returns>
		/// A <see cref="NNInfo"/>. This function will only return an empty NNInfo if there is no nodes which comply with the specified constraint.
		/// </returns>
		public virtual NNInfo GetNearestForce (Vector3 position, NNConstraint constraint) {
			Debug.LogError ("This should not be called if not GetNearest has been overriden, and if GetNearest has been overriden, you should override this function too, always return a node which returns true when passed to constraint.Suitable (node)");
			return new NNInfo ();
		}
		
		/// <summary>
		/// This will be called on the same time as Awake on the gameObject which the AstarPath script is attached to. (remember, not in the editor)
		/// Use this for any initialization code which can't be placed in Scan
		/// </summary>
		public virtual void Awake () {
		}
		
		/// <summary>
		/// SafeOnDestroy should be used when there is a risk that the pathfinding is searching through this graph when called
		/// </summary>
		public void SafeOnDestroy () {
			AstarPath.RegisterSafeNodeUpdate (OnDestroy);
		}
		
		/// <summary>
		/// Function for cleaning up references.
		/// </summary>
		/// <remarks>This will be called on the same time as OnDisable on the gameObject which the AstarPath script is attached to (remember, not in the editor)
		/// Use for any cleanup code such as cleaning up static variables which otherwise might prevent resources from being collected
		/// Use by creating a function overriding this one in a graph class, but always call base.OnDestroy () in that function.</remarks>
		public virtual void OnDestroy () {
			// Debug.Log ("Destroying Graph");
			
			//Clean up a refence to the node array so it can get collected even if a reference to this graph still exists somewhere
			nodes = null;
		}
		
		/// <summary>
		/// Scanns the graph with appropriate pre and post processing calls.
		/// Consider using AstarPath.Scan () instead since this function might screw things up if there is more than one graph.
		/// This function does not call <see cref="AstarPath.FloodFill"/>
		/// </summary>
		public void ScanGraph () {
			
			if (AstarPath.OnPreScan != null) {
				AstarPath.OnPreScan (AstarPath.active);
			}
			
			if (AstarPath.OnGraphPreScan != null) {
				AstarPath.OnGraphPreScan (this);
			}
			
			Scan ();
			
			if (AstarPath.OnGraphPostScan != null) {
				AstarPath.OnGraphPostScan (this);
			}
			
			if (AstarPath.OnPostScan != null) {
				AstarPath.OnPostScan (AstarPath.active);
			}
		}
		
		/// <summary>
		/// Scanns the graph, called from <see cref="AstarPath.Scan"/>
		/// Override this function to implement custom scanning logic
		/// </summary>
		public virtual void Scan () {
			Debug.LogError ("Scan is not implemented in this NavGraph");
		}
		
		/// <summary>
		/// Returns a color to be used for the specified node with the current debug settings (editor only)
		/// </summary>
		/// <param name="node">
		/// A <see cref="Node"/>
		/// </param>
		/// <returns>
		/// A <see cref="Color"/>
		/// </returns>
		public virtual Color NodeColor (Node node) {
			
			Color c = Color.white;
			
			switch (AstarPath.active.debugMode) {
				case GraphDebugMode.Areas:
					c = AstarColor.GetAreaColor (node.area);
					break;
				case GraphDebugMode.G:
					//c = Mathfx.IntToColor (node.g,0.5F);
					c = Color.Lerp (AstarColor.ConnectionLowLerp,AstarColor.ConnectionHighLerp, (float)node.g / (float)AstarPath.active.debugRoof);
					break;
				case GraphDebugMode.H:
					c = Color.Lerp (AstarColor.ConnectionLowLerp,AstarColor.ConnectionHighLerp, (float)node.h / (float)AstarPath.active.debugRoof);
					break;
				case GraphDebugMode.F:
					c = Color.Lerp (AstarColor.ConnectionLowLerp,AstarColor.ConnectionHighLerp, (float)node.f / (float)AstarPath.active.debugRoof);
					break;
				case GraphDebugMode.Penalty:
					c = Color.Lerp (AstarColor.ConnectionLowLerp,AstarColor.ConnectionHighLerp, (float)node.penalty / (float)AstarPath.active.debugRoof);
					break;
				/* Wasn't really usefull
				case GraphDebugMode.Position:
					float r = Mathf.PingPong (node.position.x/10000F,1F) + Mathf.PingPong (node.position.x/300000F,1F);
					float g = Mathf.PingPong (node.position.y/10000F,1F) + Mathf.PingPong (node.position.y/200000F,1F);
					float b = Mathf.PingPong (node.position.z/10000F,1F) + Mathf.PingPong (node.position.z/100000F,1F);
					
					
					c = new Color (r,g,b);
					break;
				*/
			}
			c.a *= 0.5F;
			return c;
			
		}
		
		public virtual void OnDrawGizmos (bool drawNodes) {
			
			if (nodes == null || !drawNodes) {
				if (!Application.isPlaying) {
					//Scan (0);
				}
				return;
			}
			
			for (int i=0;i<nodes.Length;i++) {
				Node node = nodes[i];
				
				if (node.connections != null) {
					
					Gizmos.color = NodeColor (node);
					if (AstarPath.active.debugPath != null && AstarPath.active.showSearchTree && (node.pathID != AstarPath.active.debugPath.pathID || Node.activePath == null)) {
						return;
					}
					
					if (node.parent != null && AstarPath.active.showSearchTree) {
						Gizmos.DrawLine (node.position,node.parent.position);
					} else {
						for (int q=0;q<node.connections.Length;q++) {
							Gizmos.DrawLine (node.position,node.connections[q].position);
						}
					}
				}
			}
		}
	}
	
	

	[System.Serializable]
	public class GraphCollision : ISerializableObject {
		
		/** Collision shape to use.
		  * Pathfinding::ColliderType */
		public ColliderType type = ColliderType.Capsule;
		
		public float diameter = 1F; /**< Diameter of capsule or sphere when checking for collision. 1 equals \link Pathfinding::GridGraph::nodeSize nodeSize \endlink. If #type is set to Ray, this does not affect anything */
		public float height = 2F; /**< Height of capsule or length of ray when checking for collision. If #type is set to Sphere, this does not affect anything */
		
		public RayDirection rayDirection = RayDirection.Both; /**< Direction of the ray when checking for collision. If #type is not Ray, this does not affect anything \note This variable is not used currently, it does not affect anything */
		
		/** Layer mask to use for collision check. This should only contain layers of objects defined as obstacles */
		public LayerMask mask;
		
		/** Layer mask to use for height check. */
		public LayerMask heightMask = -1;
		
		
		public float fromHeight = 100; /**< The height to check from when checking height */
		public bool thickRaycast = false; /**< Toggles thick raycast */
		public float thickRaycastDiameter = 1; /**< Diameter of the thick raycast in nodes. 1 equals \link Pathfinding::GridGraph::nodeSize nodeSize \endlink */
		
		public Vector3 up; /**< Direction to use as \a UP. \see Initialize */
		
		private Vector3 upheight; /**< #up * #height \see Initialize */
		private float finalRadius; /**< #diameter * scale * 0.5. Where \a scale usually is \link Pathfinding::GridGraph::nodeSize nodeSize \endlink \see Initialize */
		private float finalRaycastRadius;/**< #thickRaycastDiameter * scale * 0.5. Where \a scale usually is \link Pathfinding::GridGraph::nodeSize nodeSize \endlink \see Initialize */
		
		public bool collisionCheck = true; /**< Toggle collision check */
		public bool heightCheck = true; /**< Toggle height check. If false, the grid will be flat */
	
		/** Make nodes unwalkable when no ground was found with the height raycast. If height raycast is turned off, this doesn't affect anything. */
		public bool unwalkableWhenNoGround = true;

//#if !PhotonImplementation
		/** Sets up #up, #upheight, #finalRadius and #finalRaycastRadius using the specified matrix and scale */
		public void Initialize (Matrix4x4 matrix, float scale) {
			up = matrix.MultiplyVector (Vector3.up);
			upheight = up*height;
			finalRadius = diameter*scale*0.5F;
			finalRaycastRadius = thickRaycastDiameter*scale*0.5F;
		}
		
		/** Returns if the position is obstructed. If #collisionCheck is false, this will always return true.\n */
		public bool Check (Vector3 position) {
			
			if (!collisionCheck) {
				return true;
			}
			
			switch (type) {
				case ColliderType.Capsule:
					return !Physics.CheckCapsule (position, position+upheight,finalRadius,mask);
				case ColliderType.Sphere:
					return !Physics.CheckSphere (position, finalRadius,mask);
				default:
					switch (rayDirection) {
						case RayDirection.Both:
							return !Physics.Raycast (position, up, height, mask) && !Physics.Raycast (position+upheight, -up, height, mask);
						case RayDirection.Up:
							return !Physics.Raycast (position, up, height, mask);
						default:
							return !Physics.Raycast (position+upheight, -up, height, mask);
					}
			}
		}
		
		/** Returns the position with the correct height. If #heightCheck is false, this will return \a position.\n */
		public Vector3 CheckHeight (Vector3 position) {
			RaycastHit hit;
			bool walkable;
			return CheckHeight (position,out hit, out walkable);
		}
		
		/** Returns the position with the correct height. If #heightCheck is false, this will return \a position.\n
		  * \a walkable will be set to false if nothing was hit. The ray will check a tiny bit further than to the grids base to avoid floating point errors when the ground is exactly at the base of the grid */
		public Vector3 CheckHeight (Vector3 position, out RaycastHit hit, out bool walkable) {
			walkable = true;
			
			if (!heightCheck) {
				hit = new RaycastHit ();
				return position;
			}
			
			if (thickRaycast) {
				Ray ray = new Ray (position+up*fromHeight,-up);
				if (Physics.SphereCast (ray, finalRaycastRadius,out hit, fromHeight+0.005F, heightMask)) {
					
					return Mathfx.NearestPoint (ray.origin,ray.origin+ray.direction,hit.point);
					//position+up*(fromHeight-hit.distance);
				} else {
					if (unwalkableWhenNoGround) {
						walkable = false;
					}
				}
			} else {
				if (Physics.Raycast (position+up*fromHeight, -up,out hit, fromHeight+0.005F, heightMask)) {
					return hit.point;
				} else {
					if (unwalkableWhenNoGround) {
						walkable = false;
					}
				}
			}
			return position;
		}
		
		/** Same as #CheckHeight, except that the raycast will always start exactly at \a origin
		  * \a walkable will be set to false if nothing was hit. The ray will check a tiny bit further than to the grids base to avoid floating point errors when the ground is exactly at the base of the grid */
		public Vector3 Raycast (Vector3 origin, out RaycastHit hit, out bool walkable) {
			walkable = true;
			
			if (!heightCheck) {
				hit = new RaycastHit ();
				return origin -up*fromHeight;
			}
			
			if (thickRaycast) {
				Ray ray = new Ray (origin,-up);
				if (Physics.SphereCast (ray, finalRaycastRadius,out hit, fromHeight+0.005F, heightMask)) {
					
					return Mathfx.NearestPoint (ray.origin,ray.origin+ray.direction,hit.point);
					//position+up*(fromHeight-hit.distance);
				} else {
					if (unwalkableWhenNoGround) {
						walkable = false;
					}
				}
			} else {
				if (Physics.Raycast (origin, -up,out hit, fromHeight+0.005F, heightMask)) {
					return hit.point;
				} else {
					if (unwalkableWhenNoGround) {
						walkable = false;
					}
				}
			}
			return origin -up*fromHeight;
		}
		
		//[System.Obsolete ("Does not work well, will only return an object a single time")]
		/** Returns all hits when checking height for \a position.
		  * \note Does not work well with thick raycast, will only return an object a single time */
		public RaycastHit[] CheckHeightAll (Vector3 position) {
			
			RaycastHit[] hits;
			
			if (!heightCheck) {
				RaycastHit hit = new RaycastHit ();
				hit.point = position;
				hit.distance = 0;
				return new RaycastHit[1] {hit};
			}
			
			
			if (thickRaycast) {
				Ray ray = new Ray (position+up*fromHeight,-up);
				
				hits = Physics.SphereCastAll (ray, finalRaycastRadius, fromHeight, heightMask);
					
				for (int i=0;i<hits.Length;i++) {
					hits[i].point = Mathfx.NearestPoint (ray.origin,ray.origin+ray.direction,hits[i].point);
					//position+up*(fromHeight-hit.distance);
				}
			} else {
				hits = Physics.RaycastAll (position+up*fromHeight, -up, fromHeight, heightMask);
			}
			return hits;
		}
		
		/** \copydoc Pathfinding::ISerializableObject::SerializeSettings \copybrief Pathfinding::ISerializableObject::SerializeSettings */
		public void SerializeSettings (AstarSerializer serializer) {
			serializer.AddValue ("Mask",(int)mask);
			serializer.AddValue ("Diameter",diameter);
			serializer.AddValue ("Height",height);
			serializer.AddValue ("Type",(int)type);
			serializer.AddValue ("RayDirection",(int)rayDirection);
			
			serializer.AddValue ("heightMask",(int)heightMask);
			serializer.AddValue ("fromHeight",fromHeight);
			serializer.AddValue ("thickRaycastDiameter",thickRaycastDiameter);
			serializer.AddValue ("thickRaycast",thickRaycast);
			
			serializer.AddValue ("collisionCheck",collisionCheck);
			serializer.AddValue ("heightCheck",heightCheck);
			
			serializer.AddValue ("unwalkableWhenNoGround",unwalkableWhenNoGround);
		}
		
		/** \copydoc Pathfinding::ISerializableObject::DeSerializeSettings */
		public void DeSerializeSettings (AstarSerializer serializer) {
			mask.value = (int)serializer.GetValue ("Mask",typeof (int));
			diameter = (float)serializer.GetValue ("Diameter",typeof (float));
			height = (float)serializer.GetValue ("Height",typeof (float));
			type = (ColliderType)serializer.GetValue ("Type",typeof(int));
			rayDirection = (RayDirection)serializer.GetValue ("RayDirection",typeof(int));
			
			heightMask.value = (int)serializer.GetValue ("heightMask",typeof (int),-1);
			fromHeight = (float)serializer.GetValue ("fromHeight",typeof (float), 100.0F);
			thickRaycastDiameter = (float)serializer.GetValue ("thickRaycastDiameter",typeof (float));
			thickRaycast = (bool)serializer.GetValue ("thickRaycast",typeof (bool));
			
			collisionCheck = (bool)serializer.GetValue ("collisionCheck",typeof(bool),true);
			heightCheck = (bool)serializer.GetValue ("heightCheck",typeof(bool),true);
			
			unwalkableWhenNoGround = (bool)serializer.GetValue ("unwalkableWhenNoGround",typeof(bool),true);
			
			if (fromHeight == 0) fromHeight = 100;
			
			
		}
	}

	
	/** Determines collision check shape */
	public enum ColliderType {
		Sphere,		/**< Uses a Sphere, Physics.CheckSphere */
		Capsule,	/**< Uses a Capsule, Physics.CheckCapsule */
		Ray			/**< Uses a Ray, Physics.Linecast */
	}
	
	/** Determines collision check ray direction */
	public enum RayDirection {
		Up,	 	/**< Casts the ray from the bottom upwards */
		Down,	/**< Casts the ray from the top downwards */
		Both	/**< Casts two rays in either direction */
	}
}