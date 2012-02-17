//#define DEBUG   //"Enables some debugging messages"
using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using Pathfinding;

[CustomEditor (typeof(AstarPath))]
public class AstarPathEditor : Editor {

	//public static GraphEditor[] graphEditorTypes = new GraphEditor[2] {GridGraphEditor.active,NavMeshGraphEditor.active};
	
	/** List of all graph editors available (e.g GridGraphEditor) */
	public static Dictionary<string,CustomGraphEditor> graphEditorTypes = new Dictionary<string,CustomGraphEditor> ();/*{
		{"NavMeshGraph", NavMeshGraphEditor.NewInstance ()},
		{"GridGraph", GridGraphEditor.NewInstance ()},
		{"MultiGridGraph", MultiGridGraphEditor.NewInstance ()},
		{"LineTraceGraph", GridGraphEditor.NewInstance ()},
		{"RecastGraph", RecastGraphEditor.NewInstance ()}
	};*/
	
	/** List of all graph editors for graphs attached */
	public GraphEditor[] graphEditors;
	
	public System.Type[] graphTypes {
		get {
			return script.astarData.graphTypes;
		}
	}
	
	/** Path to the editor assets folder for the A* Pathfinding Project. If this path turns out to be incorrect, the script will try to find the correct path
	  * \see LoadStyles */
	public static string editorAssets = "Assets/AstarPathfindingProject/Editor/EditorAssets";
	
	public static string scriptsFolder = "Assets/AstarPathfindingProject";
	
	/** Alternative path to the editor assets folder for the A* Pathfinding Project. \obsolete */
	[System.ObsoleteAttribute ("This is not used anymore, the folder is searched for if it cannot be found int the default location")]
	public static string alternativeEditorAssets = "Assets/AstarPathfindingEditor/Editor/EditorAssets";
	
	/** URL to the version file containing the latest version number */
	public static string updateURL = "http://www.arongranberg.com/astar/version.php";
	
	/** URL to the documentation of the A* Pathfinding Project */
	public static string documentationURL = "http://arongranberg.com/astar/docs/";

	/** URL to more info about the A* Pathfinding Project */
	public static string astarProInfoURL = "http://arongranberg.com/unity/a-pathfinding/astarpro/";
	
	/** URL to a page with more info on modifiers */
	public static string ModifierHelpURL = "http://www.arongranberg.com/astar/docs/modifiers.php";
	
	public static string DownloadLink = "http://arongranberg.com/unity/a-pathfinding/download";
	
	public static string CRecastHelpURL = "http://www.arongranberg.com/astar/docs/class_pathfinding_1_1_recast_graph.php#a2d3655da3ed281674cf5125205e2a246";
	
	public static readonly string AstarProTooltip = "A* Pathfinding Project Pro only feature\nThe Pro version can be bought on the A* Pathfinding Project homepage,";
	public static readonly string AstarProButton  = "A* Pathfinding Project Pro only feature\nThe Pro version can be bought on the A* Pathfinding Project homepage, click here for info";
	public static WWW updateCheckObject;
	
	public static double updateCheckRate = 1F;//1.0F;	/** Number of days between update checks */
	public static System.Version latestAstarVersion; /**< Latest version of the A* Pathfinding Project */
	public static string latestAstarVersionDesc;/**< Description of the latest update of the A* Pathfinding Project */
	public static string latestAstarVersionURL;
	
	/** Toggle to use a darker skin which matches the Unity Pro dark skin */
	public static bool useDarkSkin = false;
	public static bool askForDarkSkin = false; /**< If the dark skin is detected, show a popup asking if the dark skin should be used */
	public static bool hasForcedNoDarkSkin = false; /**< True if the user answered No on #askForDarkSkin */
	
	public static bool firstRun = true;
	
	bool showAddGraphMenu = false; /**< Is the 'Add New Graph' menu open */
	
	static bool showSettings = false;
	
	//static bool debugSettings = false;
	static bool colorSettings = false;
	static bool editorSettings = false;
	static bool linkSettings = false;
	static bool editLinks = false;
	static bool aboutArea = false;
	static bool optimizationSettings = false;
	static bool customAreaColorsOpen = false;
	
	public AstarPath script;
	public EditorGUILayoutx GUILayoutx;
	
	//public SerializedObject m_object;
	
	//Styles
	
	public static bool stylesLoaded = false;
	
	public static GUISkin astarSkin;
	public static GUIStyle graphBoxStyle;
	public static GUIStyle graphDeleteButtonStyle;
	public static GUIStyle graphInfoButtonStyle;
	public static GUIStyle helpBox;
	public static GUIStyle thinHelpBox;
	public static GUIStyle upArrow;
	public static GUIStyle downArrow;
	
	//End Styles
	
	//Settings
	
	public bool enableUndo = true;
	
	//End Settings
	
	//Misc
	
	public System.DateTime lastUpdateCheck = System.DateTime.UtcNow;
	
	//End Misc
	
	
	/** Enables editor stuff. Loads graphs, reads settings and sets everything up */
	public void OnEnable () {
		
		script = target as AstarPath;
		GUILayoutx = new EditorGUILayoutx ();
		EditorGUILayoutx.editor = this;
		
		AstarSerializer.readUnityReference_Editor  = ReadUnityReference;
		AstarSerializer.writeUnityReference_Editor = WriteUnityReference;
		
		//Enables the editor to get a callback on OnDrawGizmos to enable graph editors to draw gizmos
		script.OnDrawGizmosCallback = OnDrawGizmos;
		
		// Make sure all references are set up to avoid NullReferenceExceptions
		script.SetUpReferences ();
		
		//Search the assembly for graph types and graph editors
		FindGraphTypes ();
		
		GetAstarEditorSettings ();
		
		LoadStyles ();
		
		LoadGraphs ();
		
		//Call enable on graph editors [EDIT - CheckGraphEditors () calls that now]
		/*for (int i=0;i<graphEditors.Length;i++) {
			graphEditors[i].OnEnable (script.graphs[i]);
			graphEditors[i].OnEnableUndo (script.graphs[i]);
		}*/
		
	}
	
	/** Cleans up editor stuff */
	public void OnDisable () {
		
		if (target == null) {
			return;
		}
		
		SetAstarEditorSettings ();
		CheckGraphEditors ();
		
		//This doesn't get saved by Unity anyway for some reason
		//SerializeGraphs (new AstarSerializer (script));
		
		for (int i=0;i<graphEditors.Length;i++) {
			graphEditors[i].OnDisable ();
			//graphEditors[i].OnDisableUndo ();
		}
		
		SaveGraphsAndUndo ();
		
	}
	
	/** Reads settings frome EditorPrefs */
	public void GetAstarEditorSettings () {
		EditorGUILayoutx.fancyEffects = EditorPrefs.GetBool ("EditorGUILayoutx.fancyEffects",true);
		enableUndo = EditorPrefs.GetBool ("enableUndo",false);
		
		try {
			latestAstarVersion = new System.Version (EditorPrefs.GetString ("AstarLatestVersion",AstarPath.Version.ToString ()));
		}
		catch (System.Exception) {
			Debug.LogWarning ("Invalid last version number encountered when loading from preferences");
			latestAstarVersion = AstarPath.Version;
		}
		
		try {
			lastUpdateCheck = System.DateTime.Parse (EditorPrefs.GetString ("AstarLastUpdateCheck",System.DateTime.UtcNow.ToString ()));
		}
		catch (System.FormatException) {
			lastUpdateCheck = System.DateTime.UtcNow;
			Debug.LogWarning ("Invalid DateTime string encountered when loading from preferences");
		}
		
		latestAstarVersionURL = EditorPrefs.GetString ("AstarLatestVersionURL","http://arongranberg.com/unity/a-pathfinding/");
		latestAstarVersionDesc = EditorPrefs.GetString ("AstarLatestVersionDesc");
		useDarkSkin = EditorPrefs.GetBool ("AstarUseDarkSkin",false);
		hasForcedNoDarkSkin = EditorPrefs.GetBool ("AstarForcedNoDarkSkin",false);
		askForDarkSkin = true;//EditorPrefs.GetInt ("UseDarkSkin",0) == 1;//Set by Unity
		
		editorAssets = EditorPrefs.GetString ("AstarEditorAssets",editorAssets);
		
		//Debug.Log ("Dark Skin : "+EditorPrefs.GetInt ("UseDarkSkin",0));
		
		//Check if this is the first run of the A* Pathfinding Project in this project
		string runBeforeProjects = EditorPrefs.GetString ("AstarUsedProjects","");
		using (System.Security.Cryptography.MD5 md5Hash = System.Security.Cryptography.MD5.Create()) {
            string hash = EditorUtilities.GetMd5Hash(md5Hash, Application.dataPath);
			
			string[] hashes = runBeforeProjects.Split ("|"[0]);
			firstRun = true;
			for (int i=0;i<hashes.Length;i++) {
				if (hash == hashes[i]) {
					firstRun = false;
				}
			}
		}
	}
	
	public void SetAstarEditorSettings () {
		EditorPrefs.SetBool ("EditorGUILayoutx.fancyEffects",EditorGUILayoutx.fancyEffects);
		EditorPrefs.SetBool ("enableUndo",enableUndo);
		EditorPrefs.SetBool ("AstarUseDarkSkin",useDarkSkin);
		EditorPrefs.SetBool ("AstarForcedNoDarkSkin",hasForcedNoDarkSkin);
		EditorPrefs.SetString ("AstarEditorAssets",editorAssets);
		
		//EditorPrefs.SetInt ("UseDarkSkin",useDarkSkin ? 1 : 0);
	}
	
	/** Checks if JS support is enabled. This is done by checking if the directory 'Assets/AstarPathfindingEditor/Editor' exists */
	public static bool IsJsEnabled () {
		return System.IO.Directory.Exists (Application.dataPath+"/AstarPathfindingEditor/Editor");
	}
	
	/** Enables JS support. This is done by restructuring folders in the project */
	public void EnableJs () {
		
		//Path to the project folder (not with /Assets at the end)
		string projectPath = Application.dataPath;
		if (projectPath.EndsWith ("/Assets")) {
			projectPath = projectPath.Remove (projectPath.Length-("Assets".Length));
		}
		
		if (!System.IO.Directory.Exists (projectPath + scriptsFolder)) {
			string error = "Could not enable Js support. AstarPathfindingProject folder did not exist in the default location.\n" +
				"If you get this message and the AstarPathfindingProject is not at the root of your Assets folder (i.e at Assets/AstarPathfindingProject)" +
				" then you should move it to the root";
			
			Debug.LogError (error);
			EditorUtility.DisplayDialog ("Could not enable Js support",error,"ok");
			return;
		}
		
		if (!System.IO.Directory.Exists (Application.dataPath+"/AstarPathfindingEditor")) {
			System.IO.Directory.CreateDirectory (Application.dataPath+"/AstarPathfindingEditor");
			AssetDatabase.Refresh ();
		}
		if (!System.IO.Directory.Exists (Application.dataPath+"/Plugins")) {
			System.IO.Directory.CreateDirectory (Application.dataPath+"/Plugins");
			AssetDatabase.Refresh ();
		}
		
		
		AssetDatabase.MoveAsset (scriptsFolder + "/Editor","Assets/AstarPathfindingEditor/Editor");
		AssetDatabase.MoveAsset (scriptsFolder,"Assets/Plugins/AstarPathfindingProject");
		AssetDatabase.Refresh ();
	}
	
	/** Disables JS support if it was enabled. This is done by restructuring folders in the project */
	public void DisableJs () {
		
		if (System.IO.Directory.Exists (Application.dataPath+"/Plugins/AstarPathfindingProject")) {
			string error = AssetDatabase.MoveAsset ("Assets/Plugins/AstarPathfindingProject",scriptsFolder);
			if (error != "") {
				Debug.LogError ("Couldn't disable Js - "+error);
			} else {
				try {
					System.IO.Directory.Delete (Application.dataPath+"/Plugins");
				} catch (System.Exception) {}
			}
		} else {
			Debug.LogWarning ("Could not disable JS - Could not find directory '"+Application.dataPath+"/Plugins/AstarPathfindingProject'");
		}
		
		if (System.IO.Directory.Exists (Application.dataPath+"/AstarPathfindingEditor/Editor")) {
			string error = AssetDatabase.MoveAsset ("Assets/AstarPathfindingEditor/Editor",scriptsFolder + "/Editor");
			if (error != "") {
				Debug.LogError ("Couldn't disable Js - "+error);
			} else {
				try {
					System.IO.Directory.Delete (Application.dataPath+"/AstarPathfindingEditor");
				} catch (System.Exception) {}
			}
				
		} else {
			Debug.LogWarning ("Could not disable JS - Could not find directory '"+Application.dataPath+"/AstarPathfindingEditor/Editor'");
		}
		
		AssetDatabase.Refresh ();
	}
	
	/** Discards the first run window.
	 * It will not be shown for this project again */
	public static void DiscardFirstRun () {
		string runBeforeProjects = EditorPrefs.GetString ("AstarUsedProjects","");
		using (System.Security.Cryptography.MD5 md5Hash = System.Security.Cryptography.MD5.Create()) {
            string hash = EditorUtilities.GetMd5Hash(md5Hash, Application.dataPath);
			if (!runBeforeProjects.Contains (hash)) {
				runBeforeProjects += "|"+hash;
			}
			EditorPrefs.SetString ("AstarUsedProjects",runBeforeProjects);
		}
		firstRun = false;
	}
	
	public override void OnInspectorGUI () {
		
		//Do some loading and checking
		if (!stylesLoaded) {
			if (!LoadStyles ()) {
				GUILayout.Label ("The GUISkin 'AstarEditorSkin.guiskin' in the folder "+editorAssets+"/ was not found or some custom styles in it does not exist.\nThis file is required for the A* Pathfinding Project editor.\n\nIf you are trying to add A* to a new project, please do not copy the files outside Unity, export them as a UnityPackage and import them to this project or download the package from the Asset Store or the 'scripts only' package from the A* Pathfinding Project website.\n\n\nSkin loading is done in AstarPathEditor.cs --> LoadStyles function", "HelpBox");
				return;
			} else {
				stylesLoaded = true;
			}
		}
		
		bool preChanged = GUI.changed;
		GUI.changed = false;
		
		EditorGUILayoutx.editor = this;
		
		CheckForUpdates ();
		CheckGraphEditors ();
		
		//End loading and checking
		
		EditorGUI.indentLevel = 1;
		
		EditorGUIUtility.LookLikeInspector ();
		
		EventType eT = Event.current.type;
		
		DrawMainArea ();
		
		GUILayout.Space (5);
		
		if (GUILayout.Button ("Scan")) {
			AstarPath.MenuScan ();
		}
		
		//bool reverted = HandleUndo ();
		
		//if (GUI.changed && !reverted) {
		//	SaveGraphs ();
		//}
		SaveGraphsAndUndo (eT);
		
		GUI.changed = preChanged || GUI.changed;
		
		if (GUI.changed) {
			HandleUtility.Repaint ();
		}
		
		EditorGUIUtility.LookLikeInspector ();
		//m_object.ApplyModifiedProperties ();
	}
	
	/** Loads GUISkin and sets up styles. \see #editorAssets
	  * \returns True if all styles were found, false if there was an error somewhere */
	public static bool LoadStyles () {
		
		
		//Correct paths if necessary
		
		string projectPath = Application.dataPath;
		if (projectPath.EndsWith ("/Assets")) {
			projectPath = projectPath.Remove (projectPath.Length-("Assets".Length));
		}
		
		if (!System.IO.File.Exists (projectPath + editorAssets + "/AstarEditorSkinLight.guiskin") && !System.IO.File.Exists (projectPath + editorAssets + "/AstarEditorSkin.guiskin")) {
			//Initiate search
			
			System.IO.DirectoryInfo sdir = new System.IO.DirectoryInfo (Application.dataPath);
			
			Queue<System.IO.DirectoryInfo> dirQueue = new Queue<System.IO.DirectoryInfo>();
			dirQueue.Enqueue (sdir);
			
			bool found = false;
			while (dirQueue.Count > 0) {
				System.IO.DirectoryInfo dir = dirQueue.Dequeue ();
				if (System.IO.File.Exists (dir.FullName + "/AstarEditorSkinLight.guiskin") || System.IO.File.Exists (dir.FullName + "/AstarEditorSkin.guiskin")) {
					string path = dir.FullName;
					found = true;
					//Remove data path from string to make it relative
					path = path.Replace (projectPath,"");
					
					if (path.StartsWith ("/")) {
						path = path.Remove (0,1);
					}
					
					editorAssets = path;
					Debug.Log ("Located editor assets folder to '"+editorAssets+"'");
					break;
				}
				System.IO.DirectoryInfo[] dirs = dir.GetDirectories ();
				for (int i=0;i<dirs.Length;i++) {
					dirQueue.Enqueue (dirs[i]);
				}
			}
			
			if (!found) {
				Debug.LogWarning ("Could not locate editor assets folder\nA* Pathfinding Project");
				return false;
			}
		}
		
		//End checks
		
		
		if (useDarkSkin) {
			astarSkin = AssetDatabase.LoadAssetAtPath (editorAssets + "/AstarEditorSkinDark.guiskin",typeof(GUISkin)) as GUISkin;
		} else {
			astarSkin = AssetDatabase.LoadAssetAtPath (editorAssets + "/AstarEditorSkinLight.guiskin",typeof(GUISkin)) as GUISkin;
		}
		
		/*if (astarSkin == null) {
			if (useDarkSkin) {
				astarSkin = AssetDatabase.LoadAssetAtPath (alternativeEditorAssets + "/AstarEditorSkinDark.guiskin",typeof(GUISkin)) as GUISkin;
			} else {
				astarSkin = AssetDatabase.LoadAssetAtPath (alternativeEditorAssets + "/AstarEditorSkinLight.guiskin",typeof(GUISkin)) as GUISkin;
			}
			
			if (astarSkin != null) {
				editorAssets = alternativeEditorAssets;
			}
		}*/
		
		GUISkin inspectorSkin = EditorGUIUtility.GetBuiltinSkin(EditorSkin.Inspector);
		
		if (astarSkin != null) {
			astarSkin.button = inspectorSkin.button;
			//GUI.skin = astarSkin;
		} else {
			//Load skin at old path
			astarSkin = AssetDatabase.LoadAssetAtPath (editorAssets + "/AstarEditorSkin.guiskin",typeof(GUISkin)) as GUISkin;
			if (astarSkin != null) {
				AssetDatabase.RenameAsset (editorAssets + "/AstarEditorSkin.guiskin","AstarEditorSkinLight.guiskin");
			} else {
				return false;
			}
			//Error is shown in the inspector instead
			//Debug.LogWarning ("Couldn't find 'AstarEditorSkin' at '"+editorAssets + "/AstarEditorSkin.guiskin"+"'");
			
		}
		
		EditorGUILayoutx.defaultAreaStyle = astarSkin.FindStyle ("PixelBox");
		
		if (EditorGUILayoutx.defaultAreaStyle == null) {
			return false;
		}
		
		EditorGUILayoutx.defaultLabelStyle = astarSkin.FindStyle ("BoxHeader");
		graphBoxStyle = astarSkin.FindStyle ("PixelBox3");
		graphDeleteButtonStyle = astarSkin.FindStyle ("PixelButton");
		graphInfoButtonStyle = astarSkin.FindStyle ("InfoButton");
		
		upArrow = astarSkin.FindStyle ("UpArrow");
		downArrow = astarSkin.FindStyle ("DownArrow");
	
		helpBox = inspectorSkin.FindStyle ("HelpBox");
		if (helpBox == null) helpBox = inspectorSkin.FindStyle ("Box");
		
		thinHelpBox = new GUIStyle (helpBox);
		thinHelpBox.contentOffset = new Vector2 (0,-2);
		thinHelpBox.stretchWidth = false;
		thinHelpBox.clipping = TextClipping.Overflow;
		thinHelpBox.overflow.top += 1;
		
		return true;
	}
	
	/** Checks for updates if there was some time since last check.
	 * Usually called from OnInspectorGUI.
	 * It must be called repeatedly to ensure that the result is processed */
	public void CheckForUpdates () {
		
		if (updateCheckObject != null && updateCheckObject.isDone) {
			if (!string.IsNullOrEmpty (updateCheckObject.error)) {
				Debug.LogWarning ("There was an error checking for updates for the A* Pathfinding Project\n" +
				"The error might dissapear if you switch build target from Webplayer to Standalone because of the webplayer security emulation\n" +
				updateCheckObject.error);
				return;
			}
			UpdateCheckCompleted (updateCheckObject.text);
			updateCheckObject = null;
		}
		
		if (System.DateTime.Compare (lastUpdateCheck.AddDays (updateCheckRate),System.DateTime.UtcNow) < 0) {
			Debug.Log ("Checking For Updates... " + System.DateTime.UtcNow.ToString ()+"\nA* Pathfinding Project");
			
			updateCheckObject = new WWW (updateURL+"?v="+AstarPath.Version.ToString()+"&pro="+(AstarPath.HasPro ? "1":"0")+"&check="+updateCheckRate);
			
			lastUpdateCheck = System.DateTime.UtcNow;
			EditorPrefs.SetString ("AstarLastUpdateCheck",lastUpdateCheck.ToString ());
		}
		
	}
	
	/** Handles the data from the update page */
	public void UpdateCheckCompleted (string result) {
		
		if (string.IsNullOrEmpty (result)) {
			return;
		}
		
		
		string[] splits = result.Split (new char [1] {"|"[0]});
		string versionString = splits[0];
		string descriptionString = splits.Length > 1 ? splits[1] : "";
		string url = splits.Length > 2 ? splits[2] : "http://arongranberg.com/unity/a-pathfinding/";
		/*Debug.Log (updateCheckObject.text);
		if (splits.Length > 3) {
			Debug.Log ("Split 3 "+splits[3]);
		}*/
		
		System.Version newVersion = null;
		
		try {
			newVersion = new System.Version (versionString);
		} catch (System.Exception ex) {
			Debug.LogWarning ("Couldn't parse version string. Version string to parse: "+versionString+", error: "+ex.ToString ());
			updateCheckObject = null;
			return;
		}
		
		//Debug.Log ("New version exists "+newVersion+ " Desc: "+descriptionString);
		EditorPrefs.SetString ("AstarLatestVersion",newVersion.ToString ());
		EditorPrefs.SetString ("AstarLatestVersionDesc",descriptionString);
		EditorPrefs.SetString ("AstarLatestVersionURL",url);
		latestAstarVersion = newVersion;
		latestAstarVersionDesc = descriptionString;
		latestAstarVersionURL = url;
	}
	
	/** Draws the first run dialog.
	 * Asks if the user wants to enable JS support */
	public void DrawFirstRun () {
		if (!firstRun) {
			return;
		}
		
		if (IsJsEnabled ()) {
			DiscardFirstRun ();
			return;
		}
		
		GUILayoutx.BeginFadeArea (true,"Do you want to enable Javascript support?","enableJs");
		GUILayout.Label ("Folders can be restructured to enable pathfinding calls from Js\n" +
			"This setting can be edited later in Settings-->Editor",helpBox);
		GUILayout.BeginHorizontal ();
		if (GUILayout.Button ("Yes")) {
			EnableJs ();
		}
		if (GUILayout.Button ("No")) {
			DiscardFirstRun ();
		}
		GUILayout.EndHorizontal ();
		GUILayoutx.EndFadeArea ();
	}
	
	/** Draws a dialog asking the user if he/she wants to use a dark skin */
	public void DrawDarkSkinDialog () {
		if (!askForDarkSkin || hasForcedNoDarkSkin || useDarkSkin) {
			return;
		}
		
		GUILayoutx.BeginFadeArea (true,"Use Dark Skin?","enableDarkSkin");
		GUILayout.Label ("It looks like the rest of Unity uses a dark skin\n" +
			"Do you want to use it for the A* plugin too?\n" +
			"This can be changed later in Settings-->Editor",helpBox);
		GUILayout.BeginHorizontal ();
		
		if (GUILayout.Button ("Yes")) {
			useDarkSkin = true;
			askForDarkSkin = false;
			hasForcedNoDarkSkin = false;
			LoadStyles ();
		}
		if (GUILayout.Button ("No")) {
			useDarkSkin = false;
			askForDarkSkin = false;
			hasForcedNoDarkSkin = true;
			LoadStyles ();
		}
		GUILayout.EndHorizontal ();
		GUILayoutx.EndFadeArea ();
	}
	
	/** Draws the main area in the inspector */
	public void DrawMainArea () {
		
		DrawFirstRun ();
		DrawDarkSkinDialog ();
		
		//Show the graph inspectors
		script.showGraphs = GUILayoutx.BeginFadeArea (script.showGraphs,"Graphs", "showGraphInspectors");
		
		for (int i=0;i<script.graphs.Length;i++) {
			
			NavGraph graph = script.graphs[i];
			
			GraphEditor editor = graphEditors[i];
			
			if (graph == null || editor == null) {
				return;
			}
			
			if (DrawGraph (graph, editor)) {
				return;
			}
		}
		
		//Draw the Add Graph buttons
		showAddGraphMenu = GUILayoutx.BeginFadeArea (showAddGraphMenu || script.graphs.Length == 0, "Add New Graph","AddNewGraph",graphBoxStyle);
		for (int i=0;i<graphTypes.Length;i++) {
			if (graphEditorTypes.ContainsKey (graphTypes[i].Name)) {
				if (GUILayout.Button (graphEditorTypes[graphTypes[i].Name].displayName)) {
					showAddGraphMenu = false;
					AddGraph (graphTypes[i]);
					//OnSceneGUI ();
				}
			} else {
				bool preEnabled = GUI.enabled;
				GUI.enabled = false;
				GUILayout.Label (graphTypes[i].Name + " (no editor found)","Button");
				GUI.enabled = preEnabled;
			}
		}
		GUILayoutx.EndFadeArea ();
		
		if (script.astarData.data_backup != null && script.astarData.data_backup.Length != 0) {
			GUILayoutx.BeginFadeArea (true, "Backup data detected","backupData",graphBoxStyle);
			GUILayout.Label ("Backup data was found, this can have been stored because there was an error during deserialization. Check the log.\n" +
				"If you load again and everything goes well, you can discard the backup data\n" +
				"When trying to load again, the deserializer will ignore version differences (for example 3.0 would try to load 3.0.1 files)\n" +
				"The backup data is stored in AstarData.data_backup",helpBox);
			GUILayout.BeginHorizontal ();
			if (GUILayout.Button ("Try loading data again")) {
				if (script.astarData.graphs == null || script.astarData.graphs.Length == 0
				    	|| EditorUtility.DisplayDialog ("Do you want to load from backup data?",
				                                           "Are you sure you want to load from backup data?\nThis will delete your current graphs.",
				                                           "Yes",
				                                           "Cancel")) {	
					script.astarData.data = script.astarData.data_backup;
					AstarSerializer.IgnoreVersionDifferences = true;
					LoadGraphs ();
					AstarSerializer.IgnoreVersionDifferences = false;
				}
			}
			if (GUILayout.Button ("Discard backup data")) {
				script.astarData.data_backup = null;
			}
			GUILayout.EndHorizontal ();
			GUILayoutx.EndFadeArea ();
		}
		
		GUILayoutx.EndFadeArea ();
		
		DrawLinkSettings ();
		
		//Draw the settings area
		DrawSettings ();
		
		DrawSerializationSettings ();
		
		DrawOptimizationSettings ();
		
		DrawAboutArea ();
		script.showNavGraphs = EditorGUILayout.Toggle ("Show Graphs",script.showNavGraphs);
		
	}
	
	/** Draws optimizations settings.
	 * \astarpro */
	public void DrawOptimizationSettings () {
		optimizationSettings = GUILayoutx.BeginFadeArea (optimizationSettings,"Optimization","optimization");
		
		if (GUILayoutx.DrawID ("optimization")) {
			
			GUIUtilityx.SetColor (Color.Lerp (Color.yellow,Color.white,0.5F));
			if (GUILayout.Button ("Optimizations is an "+AstarProButton,helpBox)) {
				Application.OpenURL (astarProInfoURL);
			}
			GUIUtilityx.ResetColor ();
		}
		
		GUILayoutx.EndFadeArea ();
		
	}
	
	public void DrawAboutArea () {
		
		Color tmp1 = GUI.color;
		EditorGUILayoutx.FadeArea fadeArea = GUILayoutx.BeginFadeArea (aboutArea,"aboutArea", 20,EditorGUILayoutx.defaultAreaStyle);
		Color tmp2 = GUI.color;
		GUI.color = tmp1;
		
		GUILayout.BeginHorizontal ();
		
		if (GUILayout.Button ("About",EditorGUILayoutx.defaultLabelStyle)) {
			aboutArea = !aboutArea;
			GUI.changed = true;
		}
		
		if (latestAstarVersion > AstarPath.Version) {
			tmp1 *= Color.green;
			GUI.color = tmp1;
			if (GUILayout.Button ("New Version Available! "+latestAstarVersion.ToString (),thinHelpBox,GUILayout.Height (15))) {
				Application.OpenURL (latestAstarVersionURL);
			}
			GUILayout.Space (20);
		}
		
		GUILayout.EndHorizontal ();
		
		GUI.color = tmp2;
		
		if (fadeArea.Show ()) {
			GUILayout.Label ("The A* Pathfinding Project was made by Aron Granberg\nYour current version is "+AstarPath.Version.ToString ());
			
			if (latestAstarVersion > AstarPath.Version) {
				GUILayout.Label ("A new version of the A* Pathfinding Project is available, the new version is "+latestAstarVersion.ToString ()+(latestAstarVersionDesc != null && latestAstarVersionDesc != "" ? "\n"+latestAstarVersionDesc : ""));
				
				
				
				if (GUILayout.Button ("Click here to find out more")) {
					Application.OpenURL (latestAstarVersionURL);
					//Reset last check time
					lastUpdateCheck = System.DateTime.UtcNow - new System.TimeSpan ((int)updateCheckRate*2,0,0,0,0);
					CheckForUpdates ();
				}
				
				Color tmp3 = GUI.color;
				tmp2 *= new Color (0.3F,0.9F,0.3F);
				GUI.color = tmp2;
				
				if (GUILayout.Button ("Download new version")) {
					Application.OpenURL (DownloadLink);
				}
				
				GUI.color = tmp3;
			}
			
			if (GUILayout.Button (new GUIContent ("Documentation","Open the documentation for the A* Pathfinding Project"))) {
				Application.OpenURL (documentationURL);
			}
		}
		
		GUILayoutx.EndFadeArea ();
	}
	
	public void DrawLinkSettings () {
		//linkSettings = GUILayoutx.BeginFadeArea (linkSettings,"Links", );
		
		Color tmp1 = GUI.color;
		
		GUILayoutx.BeginFadeArea (linkSettings,"linkSettings", 20,EditorGUILayoutx.defaultAreaStyle);
		
		Color tmp2 = GUI.color;
		GUI.color = tmp1;
		
		if (GUILayout.Button ("Links",EditorGUILayoutx.defaultLabelStyle)) {
			linkSettings = !linkSettings;
			Repaint ();
			HandleUtility.Repaint ();
			GUI.changed = true;
		}
		
		GUI.color = tmp2;
		
		GUIStyle helpBox = GUI.skin.FindStyle ("HelpBox");
		if (helpBox == null) helpBox = GUI.skin.FindStyle ("Box");
		
		GUILayout.Label ("Links connect two nodes and makes a direct path between them possible.",helpBox);
		
		editLinks = GUILayout.Toggle (editLinks,"Edit Links","Button");
		
		//EditorGUIUtility.LookLikeControls ();
		
		GUILayout.Label ("You can edit links in the scene view either by clicking the Add Connection button or by holding shift and clicking on two nodes.",helpBox);
		GUILayoutx.EndFadeArea ();
	}
	
	public bool DrawGraph (NavGraph graph, GraphEditor graphEditor) {
		
		//GUILayout.Label (graph.guid.ToString ());
		//GUILayoutx.BeginFadeArea (graph.open,"","graph_"+graph.guid,graphBoxStyle);
		
		/*Rect r = EditorGUILayout.BeginVertical (graphBoxStyle);
		GUI.Box (r,"",graphBoxStyle);*/
		
		Color tmp1 = GUI.color;
		GUILayoutx.BeginFadeArea (graph.open,"","graph_"+graph.guid,graphBoxStyle);
		Color tmp2 = GUI.color;
		GUI.color = tmp1;
		
		GUILayout.BeginHorizontal ();
		if (GUILayout.Button (graphEditorTypes[graph.GetType ().Name].displayName,EditorGUILayoutx.defaultLabelStyle)) {
			graph.open = !graph.open;
			if (!graph.open) {
				graph.infoScreenOpen = false;
			}
			Repaint ();
		}
		
		if (script.prioritizeGraphs) {
			if (GUILayout.Button (new GUIContent ("Up","Increase the graph priority"),GUILayout.Width (40))) {
				int index = script.astarData.GetGraphIndex (graph);
				if (index > 0) {
					NavGraph tmp = script.graphs[index-1];
					script.graphs[index-1] = graph;
					script.graphs[index] = tmp;
				}
				Repaint ();
			}
			if (GUILayout.Button (new GUIContent ("Down","Decrease the graph priority"),GUILayout.Width (40))) {
				int index = script.astarData.GetGraphIndex (graph);
				if (index < script.graphs.Length-1) {
					NavGraph tmp = script.graphs[index+1];
					script.graphs[index+1] = graph;
					script.graphs[index] = tmp;
				}
				Repaint ();
			}
		}
		if (GUILayout.Toggle (graph.infoScreenOpen,"Info",graphInfoButtonStyle)) {
			if (!graph.infoScreenOpen) {
				graph.infoScreenOpen = true;
				graph.open = true;
			}
		} else {
			graph.infoScreenOpen = false;
		}
		
		
		//GUILayout.FlexibleSpace ();
		if (GUILayout.Button ("Delete",graphDeleteButtonStyle)) {
			RemoveGraph (graph);
			return true;
		}
		GUILayout.EndHorizontal ();
		
		//if (graph.infoScreenOpen) {
			EditorGUILayoutx.FadeArea fadeArea = GUILayoutx.BeginFadeArea (graph.infoScreenOpen,"graph_info_"+graph.guid,0);
			
			if (fadeArea.Show ()) {
				EditorGUILayout.LabelField ("Nodes",graph.nodes == null ? "null" : graph.nodes.Length.ToString ());
				
				int numWalkable = 0;
				
				if (Event.current.type == EventType.Repaint) {
					if (graph.nodes != null) {
						for (int i=0;i<graph.nodes.Length;i++) {
							if (graph.nodes[i].walkable) numWalkable++;
						}
					}
				}
			
				EditorGUI.indentLevel++;
				
				EditorGUILayout.LabelField ("Walkable",graph.nodes != null ? numWalkable.ToString () : "undefined");
				EditorGUILayout.LabelField ("Unwalkable",graph.nodes != null ? (graph.nodes.Length-numWalkable).ToString () : "undefined");
				
				EditorGUI.indentLevel--;
			}
			GUILayoutx.EndFadeArea ();
		//}
		
		GUI.color = tmp2;
		
		//if (GUILayoutx.DrawID ("graph_"+graph.guid)) {
			/*if (graph.sourceModifier == null) {
				graph.sourceModifier = new ModifierHolder ();
			}
			graph.sourceModifier.activeModifier = EditorGUILayout.IntField("Modifier",graph.sourceModifier.activeModifier);*/
			
			//graphEditor.HandleUndo (graph);
			graphEditor.OnInspectorGUI (graph);
		//}
		
		GUILayoutx.EndFadeArea ();
		
		return false;
	}
	
	public void OnSceneGUI () {
		
		bool preChanged = GUI.changed;
		GUI.changed = false;
		
		script = target as AstarPath;
		
		AstarPath.active = script;
		
		if (!stylesLoaded) {
			LoadStyles ();
			return;
		}
		
		//Some GUI controls might change this to Used, so we need to grab it here
		EventType et = Event.current.type;
		
		CheckGraphEditors ();
		for (int i=0;i<script.graphs.Length;i++) {
			
			NavGraph graph = script.graphs[i];
			
			if (graph == null || graphEditors.Length <= i) {
				continue;
			}
			
			graphEditors[i].OnSceneGUI (graph);
		}
		
		DrawUserConnections ();
		
		SaveGraphsAndUndo (et);
		
		if (GUI.changed) {
			//script.astarData.data = SerializeGraphs (new AstarSerializer (script));
			EditorUtility.SetDirty (target);
			
		} else {
			GUI.changed = preChanged;
		}
	}
	
	
	public int selectedUserConnection = -1;
	
	public Node firstShiftNode;
	
	public void DrawUserConnections () {
		
		
		UserConnection[] conns = script.astarData.userConnections;
		
		if (conns == null) {
			conns = new UserConnection[0];
		}
		
		Rect r = new Rect(Screen.width - 180, Screen.height - 300, 168,252);
		
		if (editLinks) {
			//Add a small border around the window + add space for the header
			Rect r2 = r;
			r2.yMin -= 30;
			r2.xMin -= 10;
			r2.xMax += 10;
			r2.yMax += 10;
			Vector2 mouse = Event.current.mousePosition;
			
			if (r2.Contains (mouse) && Event.current.type == EventType.Layout) {
				int controlID = GUIUtility.GetControlID(1024,FocusType.Passive);
				HandleUtility.AddControl (controlID,0F);
			}
			
			if (Event.current.shift) {
				
				Ray ray = HandleUtility.GUIPointToWorldRay (Event.current.mousePosition);
				
				Node node = script.GetNearest (ray);
				
				if (firstShiftNode != null) {
					Handles.color = Color.yellow;
					Handles.SphereCap (GUIUtility.GetControlID (FocusType.Passive),firstShiftNode.position,Quaternion.identity,HandleUtility.GetHandleSize (node.position)*0.12F);
				}
				
				if (node != null) {
					Handles.color = Color.yellow;
					Handles.SphereCap (GUIUtility.GetControlID (FocusType.Passive),node.position,Quaternion.identity,HandleUtility.GetHandleSize (node.position)*0.13F);
					
					if (firstShiftNode != null) {
						Handles.DrawLine (firstShiftNode.position,node.position);
					}
					
					if (Event.current.type == EventType.MouseDown && Event.current.button == 0) {
						if (firstShiftNode == null) {
							firstShiftNode = node;
						} else {
							
							//Add a connection between 'node' and firstShiftNode
							selectedUserConnection = CreateNewUserConnection (firstShiftNode.position,node.position);
							
							firstShiftNode = null;
							Event.current.Use ();
						}
					}
				} else {
					Handles.BeginGUI ();
					GUI.Box (new Rect (Event.current.mousePosition.x+20,Event.current.mousePosition.y-2,115,18),"No graphs are scanned","HelpBox");
					//GUI.Label (new Rect (Event.current.mousePosition.x+20,Event.current.mousePosition.y-5,150,30),);
					Handles.EndGUI ();
				}
				GUI.changed = true;
			} else {
				firstShiftNode = null;
			}
		}
		
		for (int i=0;i<conns.Length;i++) {
			UserConnection conn = conns[i];
			
			int controlID = GUIUtility.GetControlID(i, FocusType.Native);
			
			if (Event.current.type == EventType.Layout && editLinks) {
				if (conn.type == ConnectionType.Connection) {
					HandleUtility.AddControl (controlID,HandleUtility.DistanceToLine (conn.p1,conn.p2)*0.5F);
				} else {
					HandleUtility.AddControl (controlID,HandleUtility.DistanceToLine (conn.p1,conn.p1)*0.5F);
				}
			}
			
			if (selectedUserConnection == i && editLinks) {
				
				conn.p1 = Handles.PositionHandle (conn.p1,Quaternion.identity);
				
				if (conn.type == ConnectionType.Connection) {
					conn.p2 = Handles.PositionHandle (conn.p2,Quaternion.identity);
				}
				
				Handles.color = new Color (0.603F,0.95F,0.28F,0.8F);
				
			} else {
				
				Handles.color = new Color (0.290F, 0.454F, 0.741F, 0.800F);
			}
			
			if (Event.current.type == EventType.MouseDown && editLinks && firstShiftNode == null) {
				if (HandleUtility.nearestControl == controlID) {
					selectedUserConnection = i;
					Event.current.Use ();
					HandleUtility.Repaint ();
				}
			}
			
			if (conn.type == ConnectionType.Connection) {
				if (conn.oneWay) {
					//Because of nothing... Why not?
					Vector3 goldenRatio = (conn.p2-conn.p1)*0.618F;
					
					Handles.ConeCap (controlID,conn.p1+goldenRatio,Quaternion.LookRotation (goldenRatio),goldenRatio.magnitude*0.07F);
					Handles.ConeCap (controlID,conn.p2-goldenRatio,Quaternion.LookRotation (goldenRatio),goldenRatio.magnitude*0.07F);
					Handles.DrawLine (conn.p1,conn.p2);
				} else {
					Handles.DrawLine (conn.p1,conn.p2);
				}
			
				if (conn.enable) {
					//Nice Blue Color
					Handles.color = new Color (0.290F, 0.454F, 0.741F, 0.600F);
				} else {
					//Nice Red Color
					Handles.color = new Color (0.651F, 0.125F, 0F, 0.6F);
				}
				
				Handles.SphereCap (controlID,conn.p1,Quaternion.identity,HandleUtility.GetHandleSize (conn.p1)*0.1F);
				Handles.SphereCap (controlID,conn.p2,Quaternion.identity,HandleUtility.GetHandleSize (conn.p2)*0.1F);
			} else {
				if (conn.enable) {
					//Nice Blue Color
					Handles.color = new Color (0.290F, 0.454F, 0.741F, 0.600F);
				} else {
					//Nice Red Color
					Handles.color = new Color (0.651F, 0.125F, 0F, 0.6F);
				}
				
				Handles.SphereCap (controlID,conn.p1,Quaternion.identity,HandleUtility.GetHandleSize (conn.p1)*0.15F);
			}
		}
		
		if (Event.current.type == EventType.Layout && linkSettings) {
			int cID = GUIUtility.GetControlID(654, FocusType.Passive);
			HandleUtility.AddDefaultControl (cID);
		}
		
		if (editLinks) {
			Handles.BeginGUI();
			//GUILayout.Window (0,r,DrawUserConnectionsWindow,"Connection");
			GUILayout.BeginArea (r,"Connection","Window");
			DrawUserConnectionsWindow ();
			GUILayout.EndArea ();
			if (GUI.Button (new Rect (r.x,r.y,16,16),"",astarSkin.FindStyle ("CloseButton"))) {
				editLinks = false;
				Repaint ();
			}
			
			Handles.EndGUI();
		} else {
			
			Handles.BeginGUI();
			
			if (GUI.Button (new Rect (Screen.width-40,Screen.height-75,30,30),"Show Links",astarSkin.FindStyle ("LinkButton"))) {
				editLinks = true;
				Repaint ();
				GUI.changed = true;
			}
			
			Handles.EndGUI();
		}
		
		//Debug.Log("id: " + GUIUtility.hotControl+" "+GUIUtility.keyboardControl+ " "+Event.current.GetTypeForControl (GUIUtility.hotControl) +" Name : "+GUI.GetNameOfFocusedControl ());
		
		/*if (Event.current.type == EventType.MouseDown) {
			if (HandleUtility.nearestControl > 0 && HandleUtility.nearestControl <= conns.Length && selectedUserConnection != HandleUtility.nearestControl-1) {
				selectedUserConnection = HandleUtility.nearestControl-1;
				HandleUtility.nearestControl = 0;
				HandleUtility.Repaint ();
				//return;
			}
		}*/
	}
	
	public void DrawUserConnectionsWindow () {
		
		UserConnection[] conns = script.astarData.userConnections;
		
		if (selectedUserConnection >= 0 && selectedUserConnection < conns.Length && Event.current.type != EventType.Used) {
			
			UserConnection conn = conns[selectedUserConnection];
			
			if (Event.current.keyCode == KeyCode.Backspace && Event.current.type == EventType.KeyDown) {
				RemoveConnection (conn);
				return;
			}
			
			conn.type = (ConnectionType)EditorGUILayout.Popup ((int)conn.type,new string[2] {"Connection","Modify Node"});
			if (conn.type == ConnectionType.Connection) {
				conn.p1 = EditorGUILayout.Vector3Field (conn.oneWay ? "Start" : "Point 1",conn.p1);
				conn.p2 = EditorGUILayout.Vector3Field (conn.oneWay ? "End" : "Point 2",conn.p2);
				
				
				conn.enable = EditorGUILayout.Toggle (new GUIContent ("Enable/Disable","Should the connection between the nodes be enabled or disabled"),conn.enable);
				conn.oneWay = EditorGUILayout.Toggle (new GUIContent ("One Way","Should this connection take affect in both ways or only in one direction"),conn.oneWay);
				
				EditorGUIUtility.LookLikeControls (70,120);
				
				GUILayout.BeginHorizontal ();
				
				
				if (!conn.doOverrideCost) {
					
					GUI.enabled = false;
					EditorGUILayout.IntField (new GUIContent ("Cost","Cost of the Connection\nDefault cost is "+Int3.Precision+" per world unit"),((Int3)(conn.p1-conn.p2)).costMagnitude,GUILayout.MaxWidth (138));
				} else {
					
					conn.overrideCost = EditorGUILayout.IntField (new GUIContent ("Cost","Cost of the Connection\nDefault cost is "+Int3.Precision+" per world unit"),conn.overrideCost,GUILayout.MaxWidth (138));
				}
				GUI.enabled = true;
				
				GUILayout.FlexibleSpace ();
				conn.doOverrideCost = GUILayout.Toggle (conn.doOverrideCost,new GUIContent ("","Override the connection cost"));
				GUILayout.EndHorizontal ();
			} else {
				
				conn.p1 = EditorGUILayout.Vector3Field ("Point",conn.p1);
				
				EditorGUIUtility.LookLikeControls (70,120);
				
				int walkability = EditorGUILayout.Popup ("Walkability",!conn.doOverrideWalkability ? 0 : (conn.enable ? 2 : 1),new string[3] {"Dont change","Unwalkable","Walkable"});
				if (walkability == 0) {
					conn.doOverrideWalkability = false;
					conn.enable = true;
				} else {
					conn.doOverrideWalkability = true;
					conn.enable = walkability == 2;
				}
				
				GUILayout.BeginHorizontal ();
				
				
				if (!conn.doOverridePenalty) {
					
					GUI.enabled = false;
					EditorGUILayout.IntField (new GUIContent ("Penalty","Penalty of the node"),0,GUILayout.MaxWidth (138));
				} else {
					conn.overridePenalty = EditorGUILayout.IntField (new GUIContent ("Penalty","Penalty of the node"),conn.overridePenalty,GUILayout.MaxWidth (138));
				}
				GUI.enabled = true;
				
				GUILayout.FlexibleSpace ();
				conn.doOverridePenalty = GUILayout.Toggle (conn.doOverridePenalty,new GUIContent ("","Change node penalty"));
				GUILayout.EndHorizontal ();
				
				//conn.enable = EditorGUILayout.Toggle (new GUIContent ("Walkability","Should the node be set to walkable or unwalkable"),conn.enable);
			}
			
			if(GUILayout.Button("Snap to closest nodes")) {
				Node node1 = script.GetNearest (conn.p1);
				Node node2 = script.GetNearest (conn.p2);
				
				if (node1 != null) conn.p1 = node1.position;
				if (node2 != null) conn.p2 = node2.position;
				
			}
			
			if (GUILayout.Button ("Remove")) {
				RemoveConnection (conn);
				return;
			}
			
			EditorGUIUtility.LookLikeInspector ();
		}
		
		GUILayout.FlexibleSpace ();
		
		if(GUILayout.Button("Add Connection")) {
			selectedUserConnection = CreateNewUserConnection (Vector3.zero, Vector3.one);
		}
	}
	
	/** Removes user connection \conn from the script.astarData.userConnections array */
	void RemoveConnection (UserConnection conn) {
		UserConnection[] conns = script.astarData.userConnections;
		List<UserConnection> connList = new List<UserConnection>(conns);
		connList.Remove (conn);
		script.astarData.userConnections = connList.ToArray ();
		selectedUserConnection = -1;
		HandleUtility.Repaint ();
		//Use the Event to avoid the annoying system beep (indicating a key which can't be used here, so we inform the system that it can... it prevents the beep anyway).
		Event.current.Use ();
		GUI.changed = true;
	}
	
	public bool showSerializationSettings = false;
	public int serializationMask = -1;
	
	public void DrawSerializationSettings () {
		
		Color tmp1 = GUI.color;
		showSerializationSettings = GUILayoutx.BeginFadeArea (showSerializationSettings,"serializationSettings",20,EditorGUILayoutx.defaultAreaStyle);
		
		Color tmp2 = GUI.color;
		GUI.color = tmp1;
		
		GUILayout.BeginHorizontal ();
		
		if (GUILayout.Button ("Save & Load",EditorGUILayoutx.defaultLabelStyle)) {
			showSerializationSettings = !showSerializationSettings;
			GUI.changed = true;
		}
		
		if (script.astarData.cacheStartup && script.astarData.data_cachedStartup != null && script.astarData.data_cachedStartup.Length > 0) {
			tmp1 *= Color.yellow;
			GUI.color = tmp1;
			
			GUILayout.Label ("Startup cached",thinHelpBox,GUILayout.Height (15));
			
			GUILayout.Space (20);
			
		}
		
		GUI.color = tmp2;
		
		GUILayout.EndHorizontal ();
		
		/** This displays the values of the serialization bitmask (what to save). Any values which has not got a name will be set to zero */
		EditorGUI.indentLevel++;
		for (int i=0;i<32;i++) {
			string bitName = AstarSerializer.SMask.BitName (i);
			
			//Bit is not used
			if (bitName == null) {
				serializationMask &= ~(1 << i);
				continue;
			}
			
			serializationMask = (serializationMask & ~(1 << i)) | (EditorGUILayout.Toggle (bitName,(serializationMask >> i & 1) != 0) ? 1 : 0) << i;
		}
		EditorGUI.indentLevel--;
		
		GUILayout.Space (5);
		
		bool preEnabled = GUI.enabled;
		
		script.astarData.cacheStartup = EditorGUILayout.Toggle (new GUIContent ("Cache startup","If enabled, will cache the graphs so they don't have to be scanned at startup"),script.astarData.cacheStartup);
		
		EditorGUILayout.LabelField ("Cache size",(script.astarData.data_cachedStartup != null ? EditorUtility.FormatBytes (script.astarData.data_cachedStartup.Length) : "null"));
		
		GUILayout.BeginHorizontal ();
		
		if (GUILayout.Button ("Generate cache")) {
			if (EditorUtility.DisplayDialog ("Scan before generating cache?","Do you want to scan the graphs before saving the cache","Scan","Don't scan")) {
				AstarPath.MenuScan ();
			}
			script.astarData.SaveCacheData (serializationMask);
		}
		
		GUI.enabled = script.astarData.data_cachedStartup != null; 
		if (GUILayout.Button ("Load from cache")) {
			if (EditorUtility.DisplayDialog ("Are you sure you want to load from cache?","Are you sure you want to load graphs from the cache, this will replace your current graphs?","Yes","Cancel")) {
				script.astarData.LoadFromCache ();
			}
		}
		
		GUILayout.EndHorizontal ();
		
		if (GUILayout.Button ("Clear Cache", GUILayout.MaxWidth (120))) {
			script.astarData.data_cachedStartup = null;
		}
		
		GUI.enabled = preEnabled;
		
		GUILayout.Label ("When using 'cache startup', the 'Nodes' toggle should always be enabled otherwise the graphs' nodes won't be saved and the caching is quite useless",helpBox);
		
		/*GUI.enabled = false;
		script.astarData.compress = EditorGUILayout.Toggle ("Compress",false);//script.astarData.compress);
		GUI.enabled = preEnabled;*/
		
		GUILayout.Space (5);
		
		GUILayout.BeginHorizontal ();
		if (GUILayout.Button ("Save to file")) {
			string path = EditorUtility.SaveFilePanel ("Save Graphs","","myGraph.graph","graph");
			
			if (path != "") {
				AstarSerializer serializer = new AstarSerializer (script);
				serializer.mask = serializationMask;
				byte[] bytes = SerializeGraphs (serializer);
				serializer.SaveToFile (path,bytes);
			}
		}
		if (GUILayout.Button ("Load from file")) {
			string path = EditorUtility.OpenFilePanel ("Load Graphs","","graph");
			
			if (path != "") {
				AstarSerializer serializer = new AstarSerializer (script);
				byte[] bytes = serializer.LoadFromFile (path);
				
				if (bytes != null) {
					DeserializeGraphs (serializer,bytes);
					CheckGraphEditors ();
				} else {
					Debug.Log ("Error deserializing graph : "+serializer.error);
				}
			}
			
		}
		
		GUILayout.EndHorizontal ();


		GUILayoutx.EndFadeArea ();
	}
	
	public void DrawSettings () {
		showSettings = GUILayoutx.BeginFadeArea (showSettings,"Settings","settings");
		
		//if (GUILayoutx.DrawID ("settings")) {
			
			GUILayoutx.BeginFadeArea (true,"Pathfinding","alwaysShow",graphBoxStyle);
			
			GUI.enabled = false;
			EditorGUILayout.Toggle (new GUIContent ("Multithreading","A* Pathfinding Project Pro Only Feature\nThe Pro version can be bought at the Unity Asset Store"),false);
			GUI.enabled = true;
			script.maxFrameTime = EditorGUILayout.FloatField ("Max Frame Time",script.maxFrameTime);
			
			script.minAreaSize = EditorGUILayout.IntField (new GUIContent ("Min Area Size","The minimum number of nodes an area must have to be granted an unique area id. Only 256 area ids are available (8 bits). This merges small areas to use the same area id and helps keeping the area count under 256. [default = 10]"),script.minAreaSize);
			
			script.heuristic = (Heuristic)EditorGUILayout.EnumPopup ("Heuristic",script.heuristic);
			
			GUILayoutx.BeginFadeArea (script.heuristic == Heuristic.Euclidean || script.heuristic == Heuristic.DiagonalManhattan,"hScale");
			if (GUILayoutx.DrawID ("hScale")) {
				EditorGUI.indentLevel++;
				script.heuristicScale = EditorGUILayout.FloatField ("Heuristic Scale",script.heuristicScale);
				EditorGUI.indentLevel--;
			}
			GUILayoutx.EndFadeArea ();
			
			script.binaryHeapSize = EditorGUILayout.IntField (new GUIContent ("Binary Heap Size","The max size of the open list during a pathfinding request. If you get errors saying the heap is too small, increase it here. A good value is about 30-50% of the number of nodes in the graphs. But it depends a lot on how the graph is structured"),script.binaryHeapSize);
			
			
			script.limitGraphUpdates = EditorGUILayout.Toggle ("Limit Graph Updates",script.limitGraphUpdates);
			
			GUILayoutx.BeginFadeArea (script.limitGraphUpdates,"graphUpdateFreq");
			if (GUILayoutx.DrawID ("graphUpdateFreq")) {
				EditorGUI.indentLevel++;
				script.maxGraphUpdateFreq = EditorGUILayout.FloatField ("Max Update Frequency (s)",script.maxGraphUpdateFreq);
				EditorGUI.indentLevel--;
			}
			GUILayoutx.EndFadeArea ();
			
			script.prioritizeGraphs = EditorGUILayout.Toggle (new GUIContent ("Prioritize Graphs","Normally, the system will search for the closest node in all graphs and choose the closest one" +
				"but if Prioritize Graphs is enabled, the first graph which has a node closer than Priority Limit will be chosen and additional search (e.g for the closest WALKABLE node) will be carried out on that graph only"),
				                                                       script.prioritizeGraphs);
			GUILayoutx.BeginFadeArea (script.prioritizeGraphs,"prioritizeGraphs");
			if (GUILayoutx.DrawID ("prioritizeGraphs")) {
				EditorGUI.indentLevel++;
				script.prioritizeGraphsLimit = EditorGUILayout.FloatField ("Priority Limit",script.prioritizeGraphsLimit);
				EditorGUI.indentLevel--;
			}
			GUILayoutx.EndFadeArea ();
				
			//Recycle paths is disabled because the feature can too easlily cause errors if users are not careful
			script.recyclePaths = false;
			//script.recyclePaths = EditorGUILayout.Toggle (new GUIContent ("Recycle paths","Recycle paths to reduce memory allocations. This will put paths in a pool to be reused over and over again. If you use this, your scripts using tht paths should copy the vectorPath array and node array (if used) because when the path is recycled, those arrays will be replaced. I.e you should not get data from it using myPath.someVariable (except when you get the path callback) because 'someVariable' might be changed when the path is recycled."),script.recyclePaths);
		
			GUILayoutx.EndFadeArea ();
			
			DrawDebugSettings ();
			DrawColorSettings ();
			DrawEditorSettings ();
		//}
		
				
		GUILayoutx.EndFadeArea ();
	}
	
	public void DrawEditorSettings () {
		
		editorSettings = GUILayoutx.BeginFadeArea (editorSettings,"Editor","editorSettings",graphBoxStyle);
		
		if (GUILayoutx.DrawID ("editorSettings")) {
			EditorGUILayoutx.fancyEffects = EditorGUILayout.Toggle ("Fancy fading effects",EditorGUILayoutx.fancyEffects);
			enableUndo = EditorGUILayout.Toggle (new GUIContent ("Experimental Undo","Enables undo operations for this editor. Works only with the graph inspectors, and doesn't always work perfect. It also causes some, harmless, but sometimes annoying debug messages"),enableUndo);
			bool preVal = useDarkSkin;
			useDarkSkin = EditorGUILayout.Toggle ("Use Dark Skin",useDarkSkin);
			if (useDarkSkin != preVal) {
				LoadStyles ();
			}
			
			if (IsJsEnabled ()) {
				if (GUILayout.Button (new GUIContent ("Disable Js Support","Revert to only enable pathfinding calls from C#"))) {
					DisableJs ();
				}
			} else {
				if (GUILayout.Button (new GUIContent ("Enable Js Support","Folders can be restructured to enable pathfinding calls from Js instead of just from C#"))) {
					EnableJs ();
				}
			}
		}
		
		GUILayoutx.EndFadeArea ();
	}
	
	public void DrawDebugSettings () {
		GUILayoutx.BeginFadeArea (true,"Debug","debugSettings",graphBoxStyle);
		
		if (GUILayoutx.DrawID ("debugSettings")) {
			
			script.logPathResults = (PathLog)EditorGUILayout.EnumPopup ("Path Log Mode",script.logPathResults);
			script.debugMode = (GraphDebugMode)EditorGUILayout.EnumPopup ("Path Debug Mode",script.debugMode);
			script.showSearchTree = EditorGUILayout.Toggle ("Show Search Tree",script.showSearchTree);
			script.showUnwalkableNodes = EditorGUILayout.Toggle ("Show Unwalkable Nodes", script.showUnwalkableNodes);
			
			if (script.showUnwalkableNodes) {
				EditorGUI.indentLevel++;
				script.unwalkableNodeDebugSize = EditorGUILayout.FloatField ("Size", script.unwalkableNodeDebugSize);
				EditorGUI.indentLevel--;
			}
			bool show = script.debugMode == GraphDebugMode.G || script.debugMode == GraphDebugMode.H || script.debugMode == GraphDebugMode.F || script.debugMode == GraphDebugMode.Penalty;
			GUILayoutx.BeginFadeArea (show,"debugRoof");
			
			if (GUILayoutx.DrawID ("debugRoof")) {
				EditorGUI.indentLevel++;
				script.debugRoof = EditorGUILayout.FloatField ("Roof",script.debugRoof);
				EditorGUI.indentLevel--;
			}
			
			GUILayoutx.EndFadeArea ();
		}
		
		GUILayoutx.EndFadeArea ();
	}
	
	public void DrawColorSettings () {
		
		colorSettings = GUILayoutx.BeginFadeArea (colorSettings,"Colors","colorSettings",graphBoxStyle);
		
		if (GUILayoutx.DrawID ("colorSettings")) {
			if (script.colorSettings == null) {
				script.colorSettings = new AstarColor ();
			}
			
			AstarColor colors = script.colorSettings;
			
			//EditorGUI.indentLevel++;
			
			colors._NodeConnection = EditorGUILayout.ColorField ("Node Connection", colors._NodeConnection);
			colors._UnwalkableNode = EditorGUILayout.ColorField ("Unwalkable Node", colors._UnwalkableNode);
			colors._BoundsHandles = EditorGUILayout.ColorField ("Bounds Handles", colors._BoundsHandles);
			
			colors._ConnectionLowLerp = EditorGUILayout.ColorField ("Connection Gradient (low)", colors._ConnectionLowLerp);
			colors._ConnectionHighLerp = EditorGUILayout.ColorField ("Connection Gradient (high)", colors._ConnectionHighLerp);
			
			colors._MeshEdgeColor = EditorGUILayout.ColorField ("Mesh Edge", colors._MeshEdgeColor);
			colors._MeshColor = EditorGUILayout.ColorField ("Mesh Color", colors._MeshColor);
			
			if (colors._AreaColors == null) {
				colors._AreaColors = new Color[0];
			}
			
			//Custom Area Colors
			customAreaColorsOpen = EditorGUILayout.Foldout (customAreaColorsOpen,"Custom Area Colors");
			if (customAreaColorsOpen) {
				EditorGUI.indentLevel+=2;
				
				for (int i=0;i<colors._AreaColors.Length;i++) {
					GUILayout.BeginHorizontal ();
					colors._AreaColors[i] = EditorGUILayout.ColorField ("Area "+i+(i == 0 ? " (not used usually)":""),colors._AreaColors[i]);
					if (GUILayout.Button (new GUIContent ("","Reset to the default color"),astarSkin.FindStyle ("SmallReset"),GUILayout.Width (20))) {
						colors._AreaColors[i] = Mathfx.IntToColor (i,1F);
					}
					GUILayout.EndHorizontal ();
				}
				
				GUILayout.BeginHorizontal ();
				
				if (colors._AreaColors.Length > 255) {
					GUI.enabled = false;
				}
				
				if (GUILayout.Button ("Add New")) {
					Color[] newcols = new Color[colors._AreaColors.Length+1];
					for (int i=0;i<colors._AreaColors.Length;i++) {
						newcols[i] = colors._AreaColors[i];
					}
					newcols[newcols.Length-1] = Mathfx.IntToColor (newcols.Length-1,1F);
					colors._AreaColors = newcols;
				}
				
				GUI.enabled = true;
				if (colors._AreaColors.Length == 0) {
					GUI.enabled = false;
				}
				
				if (GUILayout.Button ("Remove last") && colors._AreaColors.Length > 0) {
					Color[] newcols = new Color[colors._AreaColors.Length-1];
					for (int i=0;i<colors._AreaColors.Length-1;i++) {
						newcols[i] = colors._AreaColors[i];
					}
					colors._AreaColors = newcols;
				}
				GUI.enabled = true;
				GUILayout.EndHorizontal ();
				
				EditorGUI.indentLevel-=2;
			}
			
			//EditorGUI.indentLevel--;
			
			if (GUI.changed) {
				colors.OnEnable ();
				//OnSceneGUI ();
				// iHandleUtility.Repaint ();
			}
		}
		
		GUILayoutx.EndFadeArea ();
	}
	
	/** Make sure every graph has a graph editor */
	public void CheckGraphEditors (bool forceRebuild = false) {
		if (forceRebuild || graphEditors == null || script.graphs == null || script.graphs.Length != graphEditors.Length) {
				
				if (script.graphs == null) {
					script.graphs = new NavGraph[0];
				}
				
				if (graphEditors != null) {
					for (int i=0;i<graphEditors.Length;i++) {
						//graphEditors[i].OnDisableUndo ();
						graphEditors[i].OnDisable ();
						graphEditors[i].OnDestroy ();
					}
				}
				
				List<GraphEditor> editors = new List<GraphEditor>();
				
				for (int i=0;i< script.graphs.Length;i++) {
					
					NavGraph graph = script.graphs[i];
					
					GraphEditor graphEditor = CreateGraphEditor (graph.GetType ().Name);
					graphEditor.target = graph;
					graphEditor.OnEnable ();
					editors.Add (graphEditor);
				}
				
				graphEditors = editors.ToArray ();
			//}
		} else {
			for (int i=0;i< script.graphs.Length;i++) {
				
				if (graphEditors[i] == null || graphEditorTypes[script.graphs[i].GetType ().Name].editorType != graphEditors[i].GetType ()) {
					CheckGraphEditors (true);
					return;
				}
				
				graphEditors[i].target = script.graphs[i];
			}
		}
	}
	
	/** Creates a link between start and end. \see \link Pathfinding::AstarData::userConnections AstarData.userConnections \endlink */
	public int CreateNewUserConnection (Vector3 start, Vector3 end) {
		UserConnection[] conns = script.astarData.userConnections;
		
		List<UserConnection> connList = new List<UserConnection>(conns);
		UserConnection conn = new UserConnection ();
		conn.p1 = start;
		conn.p2 = end;
		connList.Add (conn);
		script.astarData.userConnections = connList.ToArray ();
		
		return script.astarData.userConnections.Length-1;
	}
	
	public void RemoveGraph (NavGraph graph) {
		GUILayoutx.RemoveID ("graph_"+graph.guid);
		script.astarData.RemoveGraph (graph);
		CheckGraphEditors ();
		GUI.changed = true;
		Repaint ();
	}
	
	public void AddGraph (System.Type type) {
		script.astarData.AddGraph (type);
		CheckGraphEditors ();
		
		GUI.changed = true;
	}
	
	/** Creates a GraphEditor for a graph */
	public GraphEditor CreateGraphEditor (string graphType) {
		
		if (graphEditorTypes.ContainsKey (graphType)) {
			GraphEditor ge = System.Activator.CreateInstance (graphEditorTypes[graphType].editorType) as GraphEditor;
			ge.editor = this;
			return ge;
		} else {
			Debug.LogError ("Couldn't find an editor for the graph type '"+graphType+"' There are "+graphEditorTypes.Count+" available graph editors");
		}
		
		GraphEditor def = new GraphEditor ();
		def.editor = this;
		return def;
	}
	
	/** Draw Editor Gizmos in graphs. This is called using a delegate OnDrawGizmosCallback in the AstarPath script.*/
	public void OnDrawGizmos () {
		
		CheckGraphEditors ();
		
		for (int i=0;i<script.graphs.Length;i++) {
			
			NavGraph graph = script.graphs[i];
			
			
			if (graph == null || graphEditors.Length <= i) {
				continue;
			}
			
			graphEditors[i].OnDrawGizmos ();
		}
		
	}
	
	public bool HandleUndo () {
		if (!enableUndo) {
			return false;
		}
		
		//The user has tried to undo something, apply that
		if (script.astarData.hasBeenReverted) {
			if (script.astarData.data == null) {
				script.astarData.data = new byte[0];
			} else {
				LoadGraphs ();
				return true;
			}
		}
		
		return false;
	}
	
	public void SaveGraphsAndUndo (EventType et = EventType.Used) {
		//Serialize the settings of the graphs
		Event e = Event.current;
		
		if (!enableUndo || e == null) {
			byte[] bytes = SerializeGraphs (new AstarSerializer (script));
			script.astarData.data = bytes;
			EditorUtility.SetDirty (target);
			return;
		}
		
		if (HandleUndo ()) {
			return;
		}
		
		//To serialize settings for a grid graph takes from 0.00 ms to 7.8 ms (usually 0.0, but sometimes jumps up to 7.8 (no values in between)
		if ((e.button == 0 && (et == EventType.MouseDown || et == EventType.MouseUp)) || (e.isKey && (e.keyCode == KeyCode.Tab || e.keyCode == KeyCode.Return)) || et == EventType.ExecuteCommand) {
			
			byte[] bytes = SerializeGraphs (new AstarSerializer (script));
			
			System.Diagnostics.Stopwatch stopWatch = new System.Diagnostics.Stopwatch();
			stopWatch.Start();
				
			
			bool isDifferent = false;
			
			if (script.astarData.data == null) {
				//Debug.LogError ("UndoState.data == null - This should not happen");
				script.astarData.data = bytes;
				EditorUtility.SetDirty (target);
				return;
			}
			
			//Check if the data is any different from the last saved data, if it isn't, don't save it
			if (bytes.Length != script.astarData.data.Length) {
				isDifferent = true;
			} else {
				for (int i=0;i<bytes.Length;i++) {
					if (bytes[i] != script.astarData.data[i]) {
						isDifferent = true;
						break;
					}
				}
			}
			
			//Only save undo if the data was different from the last saved undo
			if (isDifferent) {
				//This flag is set to true so we can detect if the object has been reverted
				script.astarData.hasBeenReverted = true;
			
				Undo.RegisterUndo (script,"A* inspector");
				
				//Assign the new data
				script.astarData.data = bytes;
				
				//Undo.SetSnapshotTarget(undoState,"A* inspector");
				//Undo.CreateSnapshot ();
				//Undo.RegisterSnapshot();
				
				script.astarData.hasBeenReverted = false;
				
				stopWatch.Stop();
				
				EditorUtility.SetDirty (target);
			}
			
			
		}
		
		
	}
	
	public void LoadGraphs () {
		//Load graphs from serialized data
		DeserializeGraphs (new AstarSerializer (script));
		
		//Make sure every graph has a graph editor
		CheckGraphEditors ();
		script.astarData.hasBeenReverted = false;
	}
	
	public byte[] SerializeGraphs (AstarSerializer serializer) {
		
		//System.Diagnostics.Stopwatch stopWatch = new System.Diagnostics.Stopwatch();
		//stopWatch.Start();
		
		CheckGraphEditors ();
		
		serializer.OpenSerialize ();
		
		script.astarData.SerializeGraphsPart (serializer);
		
		for (int i=0;i<script.graphs.Length;i++) {
			NavGraph graph = script.graphs[i];
			
			GraphEditor graphEditor = graphEditors[i];
			
			serializer.AddAnchor ("EditorSettings_"+i);
			ISerializableGraphEditor serializableEditor = graphEditor as ISerializableGraphEditor;
			if (serializableEditor != null) {
				//@Add 
				
				//Set an unique prefix for all variables in this graph
				serializer.sPrefix = i.ToString ()+"E";
				serializer.SerializeEditorSettings (graph,serializableEditor,script);
				//serializableEditor.SerializeSettings (graph,serializer);
			}
		}
		
		serializer.Close ();
		
		byte[] bytes = (serializer.writerStream.BaseStream as System.IO.MemoryStream).ToArray ();
		
		//stopWatch.Stop();
		//Debug.Log ("Serializing Graphs - Took "+stopWatch.Elapsed.ToString ());
				
		return bytes;
	}
	
	public void DeserializeGraphs (AstarSerializer serializer) {
		
		if (script.astarData.data == null || script.astarData.data.Length == 0) {
			script.astarData.graphs = new NavGraph[0];
			return;
		}
		
		DeserializeGraphs (serializer, script.astarData.data);
	}
	
	public void DeserializeGraphs (AstarSerializer serializer, byte[] data) {
		
		serializer = serializer.OpenDeserialize (data);
		
		//Deserialize the main bulk of the data
		script.astarData.DeserializeGraphsPart (serializer);
		
		CheckGraphEditors ();
		
		//Deserialize editor data
		for (int i=0;i<script.graphs.Length;i++) {
			NavGraph graph = script.graphs[i];
			
			GraphEditor graphEditor = graphEditors[i];
			
			if (serializer.MoveToAnchor ("EditorSettings_"+i)) {
				ISerializableGraphEditor serializableEditor = graphEditor as ISerializableGraphEditor;
				if (serializableEditor != null) {
					//Set an unique prefix for all variables in this graph
					serializer.sPrefix = i.ToString ()+"E";
					serializer.DeSerializeEditorSettings (graph,serializableEditor,script);
					//serializableEditor.DeSerializeSettings (graph,serializer);
				}
			}
		}
		
		serializer.Close ();
	}
	
	public void DeSerializationInterrupt (AstarSerializer serializer, bool isNewer, System.Guid g1) {
		if (EditorUtility.DisplayDialog ("Replace Graph?","Another version of this graph already exists. Do you want to replace it?","Replace","Add")) {
			serializer.replaceOldGraphs = true;
		} else {
			serializer.replaceOldGraphs = false;
		}
	}
	
	public static void WriteUnityReference (AstarSerializer serializer, UnityEngine.Object ob) {
		
		if (ob == null) {
			serializer.writerStream.Write ("");
			serializer.writerStream.Write ("");
			return;
		}
		
		string assetPath = AssetDatabase.GetAssetPath (ob);
		if (assetPath != "") {
			string guid = AssetDatabase.AssetPathToGUID (assetPath);
			serializer.writerStream.Write (guid);
		} else {
			serializer.writerStream.Write ("");
		}
	}
	
	public static UnityEngine.Object ReadUnityReference (AstarSerializer serializer, string name, int instanceID, System.Type type) {

		Object ob1 = EditorUtility.InstanceIDToObject (instanceID);
		
		//Discard if not the correct type
		if (ob1 != null && !type.IsAssignableFrom (ob1.GetType ())) {
			ob1 = null;
		}
		
		Object ob2 = null;
		
		if (ob1 != null && ob1.name == name) {
			//Debug.Log ("Loading from InstanceID + name");
			return ob1;
		}
		
		string guid = serializer.readerStream.ReadString ();
		
		if (guid != "") {
			string path = AssetDatabase.GUIDToAssetPath (guid);
			ob2 = AssetDatabase.LoadMainAssetAtPath (path);
			
			//Discard if not the correct type
			if (ob2 != null && !type.IsAssignableFrom (ob2.GetType ())) {
				ob2 = null;
			}
			
			//Debug.Log ("Got path "+path+" Got Object "+(ob2 != null));
			if (ob2 != null) {
				if (ob2 == ob1) {
					return ob2;
				}
				if (ob2.name == name) {
					return ob2;
				}
			}
		}
		
		//If any were found, return them in priority order
		if (ob2 != null) {
			return ob2;
		}
		if (ob1 != null) {
			return ob1;
		}
		return null;
	}
	
	//Searches in the current assembly for GraphEditors and NavGraph types
	public void FindGraphTypes () {
		
		//Skip if we have already found the graph types
		//if (script.astarData.graphTypes != null && script.astarData.graphTypes.Length != 0) {
		//	return;
		//}
		
		
		graphEditorTypes = new Dictionary<string,CustomGraphEditor> ();
		
		Assembly asm = Assembly.GetAssembly (typeof(AstarPathEditor));
		
		System.Type[] types = asm.GetTypes ();
		
		List<System.Type> graphList = new List<System.Type> ();
		
		string debugString = "Graph Types Found\n";
		//Iterate through the assembly for classes which inherit from GraphEditor
		foreach (System.Type type in types) {
			
			System.Type baseType = type.BaseType;
			while (baseType != null) {
				if (baseType == typeof(GraphEditor)) {
					
					System.Object[] att = type.GetCustomAttributes (false);
					
					//Loop through the attributes for the graph editor class
					foreach (System.Object attribute in att) {
						CustomGraphEditor cge = attribute as CustomGraphEditor;
						
						if (cge != null && cge.graphType != null) {
							cge.editorType = type;
							graphList.Add (cge.graphType);
							graphEditorTypes.Add (cge.graphType.Name,cge);
							debugString += "-- "+cge.graphType.Name +"\n";
						}
						
					}
					break;
				}
				
				baseType = baseType.BaseType;
			}
		}
		
		
		
		asm = Assembly.GetAssembly (typeof(AstarPath));
		types = asm.GetTypes ();
		
		bool anyWithoutEditor = false;
		//Not really required, but it's so fast so why not make a check and see if any graph types didn't have any editors
		foreach (System.Type type in types) {
			
			System.Type baseType = type.BaseType;
			while (baseType != null) {
				if (baseType == typeof(NavGraph)) {
					
					bool alreadyFound = false;
					for (int i=0;i<graphList.Count;i++) {
						if (graphList[i] == type) {
							alreadyFound = true;
							break;
						}
					}
					if (!alreadyFound) {
						graphList.Add (type);
						anyWithoutEditor = true;
						debugString += "-- "+type.Name+" was found, but it has no editor";
					}
					break;
				}
				
				baseType = baseType.BaseType;
			}
		}
		
		script.astarData.graphTypes = graphList.ToArray ();
		
		debugString += "\n"+script.astarData.graphTypes.Length+" in total\n";
		
		//Dont warn about this anymore since it now shows in the editor's Add Graph area
		if (anyWithoutEditor) {
			//Debug.Log ("Some Graph Generators without editors were found:\n"+debugString);
		}
		
	}
	
}

//[System.AttributeUsageAttribute (System.AttributeUsageAttribute.AllowMultiple = true)]
[System.AttributeUsage(System.AttributeTargets.All, Inherited = false, AllowMultiple = true)]
public class CustomGraphEditor : System.Attribute {
	public System.Type graphType;
	public string displayName;
	public System.Type editorType;
	
	public CustomGraphEditor (System.Type t,string displayName) {
		graphType = t;
		this.displayName = displayName;	
	}
}

public class GraphEditor {
	
	public NavGraph target;
	private GraphUndo undoState;
	public AstarPathEditor editor;
	
	public virtual void OnEnable () {
	}
	
	public virtual void OnDisable () {
	}
	
	public virtual void OnDestroy () {
	}
	
	public Object ObjectField (string label, Object obj, System.Type objType, bool allowSceneObjects) {
		return ObjectField (new GUIContent (label),obj,objType,allowSceneObjects);
	}
	
	public Object ObjectField (GUIContent label, Object obj, System.Type objType, bool allowSceneObjects) {
		
#if UNITY_3_3
		allowSceneObjects = true;
#endif
		
#if UNITY_3_3
		obj = EditorGUILayout.ObjectField (label, obj, objType);
#else
		obj = EditorGUILayout.ObjectField (label, obj, objType, allowSceneObjects);
#endif
		
		if (obj != null) {
			if (allowSceneObjects && !EditorUtility.IsPersistent (obj)) {
				//Object is in the scene
				Component com = obj as Component;
				GameObject go = obj as GameObject;
				if (com != null) {
					go = com.gameObject;
				}
				if (go != null) {
					UnityReferenceHelper urh = go.GetComponent<UnityReferenceHelper> ();
					if (urh == null) {
						
						if (FixLabel ("Object's GameObject must have a UnityReferenceHelper component attached")) {
							go.AddComponent<UnityReferenceHelper>();
						}	
					}
				}
				
			} else if (EditorUtility.IsPersistent (obj)) {
				
				string path = AssetDatabase.GetAssetPath (obj);
				
				if (!path.Contains ("Resources/")) {
					if (FixLabel ("Object must be in the 'Resources' folder")) {
						if (!System.IO.Directory.Exists (Application.dataPath+"/Resources")) {
							System.IO.Directory.CreateDirectory (Application.dataPath+"/Resources");
							AssetDatabase.Refresh ();
						}
						string ext = System.IO.Path.GetExtension(path);
						
						string error = AssetDatabase.MoveAsset	(path,"Assets/Resources/"+obj.name+ext);
						
						if (error == "") {
							//Debug.Log ("Successful move");
						} else {
							Debug.LogError ("Couldn't move asset - "+error);
						}
					}
				}
				
				if (!AssetDatabase.IsMainAsset (obj) && obj.name != AssetDatabase.LoadMainAssetAtPath (path).name) {
					if (FixLabel ("Due to technical reasons, the main asset must have the same name as the refereced asset")) {
						string error = AssetDatabase.RenameAsset (path,obj.name);
						if (error == "") {
							//Debug.Log ("Successful");
						} else {
							Debug.LogError ("Couldn't rename asset - "+error);
						}
					}
				}
			}
		}
		
		return obj;
	}
	
	/*public void OnDisableUndo () {
		return;
		if (!editor.enableUndo) {
			return;
		}
		
		if (undoState != null) {
			ScriptableObject.DestroyImmediate (undoState);
			undoState = null;
		}
	}
	
	private void ApplyUndo () {
		return;
		if (!editor.enableUndo) {
			return;
		}
		
		undoState.hasBeenReverted = false;
		
		if (AstarPath.active == null) {
			return;
		}
		
		byte[] bytes = GetSerializedBytes (target);
			
		bool isDifferent = false;
		
		//Check if the data is any different from the last saved data, if it isn't, don't load it
		if (undoState.data == null || bytes.Length != undoState.data.Length) {
			isDifferent = true;
		} else {
			for (int i=0;i<bytes.Length;i++) {
				if (bytes[i] != undoState.data[i]) {
					isDifferent = true;
					break;
				}
			}
		}
		
		if (isDifferent) {
			
			Debug.Log ("The undo is different "+ Event.current.type +" "+Event.current.commandName);
			//Event.current.Use ();
			AstarSerializer sz = new AstarSerializer (editor.script);
			sz.OpenDeserialize (undoState.data);
			sz.DeSerializeSettings (target,AstarPath.active);
			sz.Close ();
		}
	}
	
	public void ModifierKeysChanged () {
		return;
		if (!editor.enableUndo) {
			return;
		}
		
		if (undoState == null) {
			return;
		}
		//The user has tried to undo something, apply that
		if (undoState.hasBeenReverted) {
			ApplyUndo ();
			GUI.changed = true;
			editor.Repaint ();
		}
		
	}
	
	/** Handles undo operations for the graph *
	public void HandleUndo (NavGraph target) {
		return;
		if (!editor.enableUndo) {
			return;
		}
		
		if (undoState == null) {
			undoState = ScriptableObject.CreateInstance<GraphUndo>();
		}
		
		Event e = Event.current;
		
		//ModifierKeysChanged ();
		
		//To serialize settings for a grid graph takes from 0.00 ms to 7.8 ms (usually 0.0, but sometimes jumps up to 7.8 (no values in between)
		if ((e.button == 0 && (e.type == EventType.MouseDown || e.type == EventType.MouseUp)) || (e.isKey && (e.keyCode == KeyCode.Tab || e.keyCode == KeyCode.Return))) {
			System.Diagnostics.Stopwatch stopWatch = new System.Diagnostics.Stopwatch();
			stopWatch.Start();
				
			//Serialize the settings of the graph
			byte[] bytes = GetSerializedBytes (target);
			
			bool isDifferent = false;
			
			if (undoState.data == null) {
				Debug.LogError ("UndoState.data == null - This should not happen");
				return;
			}
			
			//Check if the data is any different from the last saved data, if it isn't, don't save it
			if (bytes.Length != undoState.data.Length) {
				isDifferent = true;
			} else {
				for (int i=0;i<bytes.Length;i++) {
					if (bytes[i] != undoState.data[i]) {
						isDifferent = true;
						break;
					}
				}
			}
			
			//Only save undo if the data was different from the last saved undo
			if (isDifferent) {
				//This flag is set to true so we can detect if the object has been reverted
				undoState.hasBeenReverted = true;
			
				Undo.RegisterUndo (undoState,"A* inspector");
				
				//Assign the new data
				undoState.data = bytes;
				
				//Undo.SetSnapshotTarget(undoState,"A* inspector");
				//Undo.CreateSnapshot ();
				//Undo.RegisterSnapshot();
				
				undoState.hasBeenReverted = false;
				Debug.Log ("Saved "+bytes.Length+" bytes");
				stopWatch.Stop();
				Debug.Log ("Adding Undo "+stopWatch.Elapsed.ToString ());
			}
			
			
		}
	}*/
	
	/** Returns a byte array with the settings of the graph. This function serializes the graph's settings and stores them in a byte array, used for undo operations. This will not save any additional metadata such as which A* version we are working on. */
	private byte[] GetSerializedBytes (NavGraph target) {
		//Serialize the settings of the graph
		AstarSerializer sz = new AstarSerializer (editor.script);
		sz.OpenSerialize ();
		sz.SerializeSettings (target,AstarPath.active);
		sz.Close ();
		byte[] bytes = (sz.writerStream.BaseStream as System.IO.MemoryStream).ToArray ();
		
		return bytes;
	}
	
	/** Override to implement graph inspectors */
	public virtual void OnInspectorGUI (NavGraph target) {
	}
	
	/** Override to implement scene GUI drawing for the graph */
	public virtual void OnSceneGUI (NavGraph target) {
	}
	
	/** Override to implement scene Gizmos drawing for the graph */
	public virtual void OnDrawGizmos () {
	}
	
	/** Draws a thin separator line */
	public void Separator () {
		GUIStyle separator = AstarPathEditor.astarSkin.FindStyle ("PixelBox3Separator");
		if (separator == null) {
			separator = new GUIStyle ();
		}
		
		Rect r = GUILayoutUtility.GetRect (new GUIContent (),separator);
		
		if (Event.current.type == EventType.Repaint) {
			separator.Draw (r,false,false,false,false);
		}
	}
	
	/** Draws a small help box with a 'Fix' button to the right. \returns Boolean - Returns true if the button was clicked */
	public bool FixLabel (string label, string buttonLabel = "Fix", int buttonWidth = 40) {
		bool returnValue = false;
		GUILayout.BeginHorizontal ();
		GUILayout.Space (14*EditorGUI.indentLevel);
		GUILayout.BeginHorizontal (AstarPathEditor.helpBox);
		GUILayout.Label (label, EditorStyles.miniLabel,GUILayout.ExpandWidth (true));
		if (GUILayout.Button (buttonLabel,EditorStyles.miniButton,GUILayout.Width (buttonWidth))) {
			returnValue = true;
		}
		GUILayout.EndHorizontal ();
		GUILayout.EndHorizontal ();
		return returnValue;
	}
	
	/** Draws a small help box. Works with EditorGUI.indentLevel */
	public void HelpBox (string label) {
		GUILayout.BeginHorizontal ();
		GUILayout.Space (14*EditorGUI.indentLevel);
		GUILayout.Label (label, AstarPathEditor.helpBox);
		GUILayout.EndHorizontal ();
	}
	
	/** Draws a toggle with a bold label to the right. Does not enable or disable GUI */
	public bool ToggleGroup (string label, bool value) {
		return ToggleGroup (new GUIContent (label),value);
	}
	
	/** Draws a toggle with a bold label to the right. Does not enable or disable GUI */
	public bool ToggleGroup (GUIContent label, bool value) {
		GUILayout.BeginHorizontal ();
		GUILayout.Space (13*EditorGUI.indentLevel);
		value = GUILayout.Toggle (value,"",GUILayout.Width (10));
		GUIStyle boxHeader = AstarPathEditor.astarSkin.FindStyle ("CollisionHeader");
		if (GUILayout.Button (label,boxHeader, GUILayout.Width (100))) {
			value = !value;
		}
		
		GUILayout.EndHorizontal ();
		return value;
	}
	
	/** Draws the inspector for a \link Pathfinding::GraphCollision GraphCollision class \endlink */
	public void DrawCollisionEditor (GraphCollision collision) {
		
		if (collision == null) {
			collision = new GraphCollision ();
		}
		
		/*GUILayout.Space (5);
		Rect r = EditorGUILayout.BeginVertical (AstarPathEditor.graphBoxStyle);
		GUI.Box (r,"",AstarPathEditor.graphBoxStyle);
		GUILayout.Space (2);*/
		Separator ();
		
		/*GUILayout.BeginHorizontal ();
		GUIStyle boxHeader = AstarPathEditor.astarSkin.FindStyle ("CollisionHeader");
		GUILayout.Label ("Collision testing",boxHeader);
		collision.collisionCheck = GUILayout.Toggle (collision.collisionCheck,"");
		
		bool preEnabledRoot = GUI.enabled;
		GUI.enabled = collision.collisionCheck;
		GUILayout.EndHorizontal ();*/
		collision.collisionCheck = ToggleGroup ("Collision testing",collision.collisionCheck);
		bool preEnabledRoot = GUI.enabled;
		GUI.enabled = collision.collisionCheck;
		
		//GUILayout.BeginHorizontal ();
		collision.type = (ColliderType)EditorGUILayout.EnumPopup("Collider type",collision.type);
		//new string[3] {"Sphere","Capsule","Ray"}
		
		bool preEnabled = GUI.enabled;
		if (collision.type != ColliderType.Capsule && collision.type != ColliderType.Sphere) {
			GUI.enabled = false;
		}
		collision.diameter = EditorGUILayout.FloatField ("Diameter",collision.diameter);
		
		GUI.enabled = preEnabled;
		
		if (collision.type != ColliderType.Capsule && collision.type != ColliderType.Ray) {
			GUI.enabled = false;
		}
		collision.height = EditorGUILayout.FloatField ("Height/Length",collision.height);
		GUI.enabled = preEnabled;
		
		//collision.mask = 1 << EditorGUILayout.LayerField ("Mask",Mathf.Clamp ((int)Mathf.Log (collision.mask,2),0,31));
		
		collision.mask = EditorGUILayoutx.LayerMaskField ("Mask",collision.mask);
		
		GUILayout.Space (2);
		
		
		GUI.enabled = preEnabledRoot;
		
		collision.heightCheck = ToggleGroup ("Height testing",collision.heightCheck);
		GUI.enabled = collision.heightCheck && GUI.enabled;
		/*GUILayout.BeginHorizontal ();
		GUILayout.Label ("Height testing",boxHeader);
		collision.heightCheck = GUILayout.Toggle (collision.heightCheck,"");
		GUI.enabled = collision.heightCheck;
		GUILayout.EndHorizontal ();*/
		
		collision.fromHeight = EditorGUILayout.FloatField ("Ray length",collision.fromHeight);
		
		collision.heightMask = EditorGUILayoutx.LayerMaskField ("Mask",collision.heightMask);
		//collision.heightMask = 1 << EditorGUILayout.LayerField ("Mask",Mathf.Clamp ((int)Mathf.Log (collision.heightMask,2),0,31));
		
		collision.thickRaycast = EditorGUILayout.Toggle ("Thick Raycast",collision.thickRaycast);
		
		editor.GUILayoutx.BeginFadeArea (collision.thickRaycast,"thickRaycastDiameter");
		
		if (editor.GUILayoutx.DrawID ("thickRaycastDiameter")) {
			EditorGUI.indentLevel++;
			collision.thickRaycastDiameter = EditorGUILayout.FloatField ("Diameter",collision.thickRaycastDiameter);
			EditorGUI.indentLevel--;
		}
		
		editor.GUILayoutx.EndFadeArea ();
		
		collision.unwalkableWhenNoGround = EditorGUILayout.Toggle (new GUIContent ("Unwalkable when no ground","Make nodes unwalkable when no ground was found with the height raycast. If height raycast is turned off, this doesn't affect anything"), collision.unwalkableWhenNoGround);
		
		GUI.enabled = preEnabledRoot;
		
		//GUILayout.Space (2);
		//EditorGUILayout.EndVertical ();
		//GUILayout.Space (5);
	}
	
	/** Draws a wire cube using handles */
	public static void DrawWireCube (Vector3 center, Vector3 size) {
		
		size *= 0.5F;
		
		Vector3 dx = new Vector3 (size.x,0,0);
		Vector3 dy = new Vector3 (0,size.y,0);
		Vector3 dz = new Vector3 (0,0,size.z);
		
		Vector3 p1 = center-dy-dz-dx;
		Vector3 p2 = center-dy-dz+dx;
		Vector3 p3 = center-dy+dz+dx;
		Vector3 p4 = center-dy+dz-dx;
		
		Vector3 p5 = center+dy-dz-dx;
		Vector3 p6 = center+dy-dz+dx;
		Vector3 p7 = center+dy+dz+dx;
		Vector3 p8 = center+dy+dz-dx;
		
		/*Handles.DrawAAPolyLine (new Vector3[4] {p1,p2,p3,p4});
		Handles.DrawAAPolyLine (new Vector3[4] {p5,p6,p7,p8});
		
		Handles.DrawAAPolyLine (new Vector3[2] {p1,p5});
		Handles.DrawAAPolyLine (new Vector3[2] {p2,p6});
		Handles.DrawAAPolyLine (new Vector3[2] {p3,p7});
		Handles.DrawAAPolyLine (new Vector3[2] {p4,p8});*/
		
		Handles.DrawLine (p1,p2);
		Handles.DrawLine (p2,p3);
		Handles.DrawLine (p3,p4);
		Handles.DrawLine (p4,p1);
		
		Handles.DrawLine (p5,p6);
		Handles.DrawLine (p6,p7);
		Handles.DrawLine (p7,p8);
		Handles.DrawLine (p8,p5);
		
		Handles.DrawLine (p1,p5);
		Handles.DrawLine (p2,p6);
		Handles.DrawLine (p3,p7);
		Handles.DrawLine (p4,p8);
	}
	
	/** \cond */
	public static Texture2D lineTex;
	
	/** \deprecated Test function, might not work. Uses undocumented editor features */
	public static void DrawAALine (Vector3 a, Vector3 b) {
		
		if (lineTex == null) {
			lineTex = new Texture2D (1,4);
			lineTex.SetPixels (new Color[4] {
				Color.clear,
				Color.black,
				Color.black,
				Color.clear,
			});
			lineTex.Apply ();
		}
		
		SceneView c = SceneView.lastActiveSceneView;
		
		Vector3 tangent1 = Vector3.Cross ((b-a).normalized, c.camera.transform.position-a).normalized;
		
		Handles.DrawAAPolyLine (lineTex,new Vector3[3] {a,b,b+tangent1*10});//,b+tangent1,a+tangent1});
	}
	/** \endcond */
}