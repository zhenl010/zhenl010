using UnityEngine;
using System.Collections;
using Pathfinding;

/** Example AI */
[RequireComponent (typeof(Seeker))]
[RequireComponent (typeof(CharacterController))]
public class AIFollow : MonoBehaviour {
	
	/** Target to move to */
	public Transform target;
	
	/** How often to search for a new path */
	public float repathRate = 0.1F;
	
	/** The minimum distance to a waypoint to consider it as "reached" */
	public float pickNextWaypointDistance = 1F;
	
	/** The minimum distance to the end point of a path to consider it "reached" (multiplied with #pickNextWaypointDistance).
	 * This value is multiplied with #pickNextWaypointDistance before it is used. Recommended range [0...1] */
	public float targetReached = 0.2F;
	
	/** Units per second */
	public float speed = 5;
	
	/** How fast the AI can turn around */
	public float rotationSpeed = 1;
	
	public bool drawGizmos = false;
	
	/** Should paths be searched for.
	 * Setting this to false will make the AI not search for paths anymore, can save some CPU cycles.
	 * It will check every #repathRate seconds if it should start to search for paths again.
	 * \note It will not cancel paths which are currently being calculated */
	public bool canSearch = true;
	
	/** Can it move. Enables or disables movement and rotation */
	public bool canMove = true;
	
	/** Seeker component which handles pathfinding calls */
	protected Seeker seeker;
	
	/** CharacterController which handles movement */
	protected CharacterController controller;
	
	/** NavmeshController which handles movement if not null*/
	protected NavmeshController navmeshController;
	
	
	/** Transform, cached because of performance */
	protected Transform tr;
	
	protected float lastPathSearch = -9999;
	
	protected int pathIndex = 0;
	
	/** This is the path the AI is currently following */
	protected Vector3[] path;
	
	/** Use this for initialization */
	public void Start () {
		seeker = GetComponent<Seeker>();
		controller = GetComponent<CharacterController>();
		navmeshController = GetComponent<NavmeshController>();
		
		
		tr = transform;
		Repath ();
	}
	
	/** Called when a path has completed it's calculation */
	public void OnPathComplete (Path p) {
		
		/*if (Time.time-lastPathSearch >= repathRate) {
			Repath ();
		} else {*/
			//StartCoroutine (WaitToRepath ());
		//}
		
		//If the path didn't succeed, don't proceed
		if (p.error) {
			return;
		}
		
		//Get the calculated path as a Vector3 array
		path = p.vectorPath;
		
		//Find the segment in the path which is closest to the AI
		//If a closer segment hasn't been found in '6' iterations, break because it is unlikely to find any closer ones then
		float minDist = Mathf.Infinity;
		int notCloserHits = 0;
		
		for (int i=0;i<path.Length-1;i++) {
			float dist = Mathfx.DistancePointSegmentStrict (path[i],path[i+1],tr.position);
			if (dist < minDist) {
				notCloserHits = 0;
				minDist = dist;
				pathIndex = i+1;
			} else if (notCloserHits > 6) {
				break;
			}
		}
	}
	
	/** Waits the remaining time until the AI should issue a new path request.
	 * The remaining time is defined by Time.time - lastPathSearch */
	public IEnumerator WaitToRepath () {
		float timeLeft = repathRate - (Time.time-lastPathSearch);
		
		yield return new WaitForSeconds (timeLeft);
		Repath ();
	}
	
	/** Stops the AI.
	 * Also stops new search queries from being made
	 * \version Before 3.0.8 This does not prevent new path calls from making the AI move again
	 * \see #Resume
	 * \see #canMove
	 * \see #canSearch */
	public void Stop () {
		canMove = false;
		canSearch = false;
	}
	
	/** Resumes walking and path searching the AI.
	 * \version Added in 3.0.8
	 * \see #Stop
	 * \see #canMove
	 * \see #canSearch */
	public void Resume () {
		canMove = true;
		canSearch = true;
	}
	
	/** Recalculates the path to #target.
	  * Queries a path request to the Seeker, the path will not be calculated instantly, but will be put on a queue and calculated as fast as possible.
	  * It will wait if the current path request by this seeker has not been completed yet.
	  * \see Seeker::IsDone */
	public virtual void Repath () {
		lastPathSearch = Time.time;
		
		if (seeker == null || target == null || !canSearch || !seeker.IsDone ()) {
			StartCoroutine (WaitToRepath ());
			return;
		}
		
		Debug.Log("Recalculate Path");
		
		//Start a new path from transform.positon to target.position, return the result to the function OnPathComplete
		seeker.StartPath (transform.position,target.position,OnPathComplete);
	}
	
	/** Start a new path moving to \a targetPoint */
	public void PathToTarget (Vector3 targetPoint) {
		lastPathSearch = Time.time;
		
		if (seeker == null) {
			return;
		}
		
		//Start a new path from transform.positon to target.position, return the result to OnPathComplete
		seeker.StartPath (transform.position,targetPoint,OnPathComplete);
	}
	
	/** Called when the AI reached the end of path.
	 * This will be called once for every path it completes, so if you have a really fast repath rate it will call this function often if when it stands on the end point.
	 */
	public virtual void ReachedEndOfPath () {
		//The AI has reached the end of the path
	}
	
	/** Update is called once per frame */
	public void Update () {
		
		if (path == null || pathIndex >= path.Length || pathIndex < 0 || !canMove) {
			return;
		}
		
		Debug.Log(path.Length);
		Debug.Log(pathIndex);
		
		//Change target to the next waypoint if the current one is close enough
		Vector3 currentWaypoint = path[pathIndex];
		
		Debug.Log((currentWaypoint - tr.position).sqrMagnitude);
		Debug.Log(pickNextWaypointDistance*pickNextWaypointDistance);
		
		//currentWaypoint.y = tr.position.y;
		while ((currentWaypoint - tr.position).sqrMagnitude < pickNextWaypointDistance*pickNextWaypointDistance) {
			pathIndex++;
			
			
			
			if (pathIndex >= path.Length) {
				//Use a lower pickNextWaypointDistance for the last point. If it isn't that close, then decrement the pathIndex to the previous value and break the loop
				if ((currentWaypoint - tr.position).sqrMagnitude < (pickNextWaypointDistance*targetReached)*(pickNextWaypointDistance*targetReached)) {
					ReachedEndOfPath ();
					Debug.Log("Reached End of Path");
					Debug.Log((currentWaypoint - tr.position).sqrMagnitude);
					
					return;
				} else {
					pathIndex--;
					Debug.Log("reduce path index");
					Debug.Log((currentWaypoint - tr.position).sqrMagnitude);
					//Break the loop, otherwise it will try to check for the last point in an infinite loop
					break;
				}
			}
			currentWaypoint = path[pathIndex];
			
			
			Debug.Log(path[pathIndex+1]);	
			//currentWaypoint.y = tr.position.y;
		}
		
		Debug.Log(currentWaypoint);
		
		Vector3 dir = currentWaypoint - tr.position;
		
		// Rotate towards the target
		//tr.rotation = Quaternion.Slerp (tr.rotation, Quaternion.LookRotation(dir), rotationSpeed * Time.deltaTime);
		//tr.eulerAngles = new Vector3(0, tr.eulerAngles.y, 0);
		
		// FEI_TODO: will use forward later since the shark model's forward is not set up well for unity environment
		//Move Forwards - forwardDir is already normalized
		/*
		Vector3 forwardDir = transform.forward;
		
		forwardDir = forwardDir * speed;
		
		float dotProd = Vector3.Dot (dir.normalized, tr.forward);
		if (dotProd == 0f) 
			dotProd = 0.2f;
		
		Debug.Log(forwardDir);
		Debug.Log(dotProd);
		
		forwardDir *= Mathf.Clamp01 (dotProd);
		Debug.Log(forwardDir);
		*/
		//Debug.Log(dir);
		
		//dir = tr.TransformDirection(dir);
		Debug.Log(dir.magnitude);
		Debug.Log(dir);
		Debug.Log(dir.normalized);
		
		Vector3 forwardDir;
		if (dir.magnitude > 1f){
			forwardDir = dir.normalized * speed;  
		}else{
			forwardDir = dir * speed;  
		}

		Debug.Log(forwardDir);
		
		if (navmeshController != null) {
			navmeshController.SimpleMove (tr.position,forwardDir);
		} else {
			controller.Move (forwardDir);
		}
		
	}
	
	/** Draws helper gizmos.
	 * Currently draws a circle around the current target point with the size showing how close the AI need to get to it for it to count as "reached".
	 */
	public void OnDrawGizmos () {
		
		if (!drawGizmos || path == null || pathIndex >= path.Length || pathIndex < 0) {
			return;
		}
		
		Vector3 currentWaypoint = path[pathIndex];
		currentWaypoint.y = tr.position.y;
		
		Debug.DrawLine (transform.position,currentWaypoint,Color.blue);
		
		float  rad = pickNextWaypointDistance;
		if (pathIndex == path.Length-1) {
			rad *= targetReached;
		}
		
		Vector3 pP = currentWaypoint + rad*new Vector3 (1,0,0);
		for (float i=0;i<2*System.Math.PI;i+= 0.1F) {
			Vector3 cP = currentWaypoint + new Vector3 ((float)System.Math.Cos (i)*rad,0,(float)System.Math.Sin(i)*rad);
			Debug.DrawLine (pP,cP,Color.yellow);
			pP = cP;
		}
		Debug.DrawLine (pP, currentWaypoint + rad*new Vector3 (1,0,0),Color.yellow);
	}
	
}
