//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
// data
private var gui : GUITexture;								// heater graphic

//**************************************************************
//**************************************************************
function Start()
{
	// Cache this component at startup instead of looking up every frame	
	gui = GetComponent( GUITexture );
	gui.pixelInset.height = Screen.height*0.5;
	gui.pixelInset.width = Screen.width*0.05;
	gui.pixelInset.x = Screen.width*0.05;
	gui.pixelInset.y = Screen.height*(1-0.05) - gui.pixelInset.height;
	
}

//
function OnGUI () {

	// FEI_TODO: will remove it after deploying it to iphone
	gui.pixelInset.height = Screen.height*0.5;
	gui.pixelInset.width = Screen.width*0.05;
	gui.pixelInset.x = Screen.width*0.05;
	gui.pixelInset.y = Screen.height*(1-0.05) - gui.pixelInset.height;

	// Weapon Heater
	/*GUILayout.BeginArea( Rect(0f, (Screen.height*0.5f - 5f), Screen.width*0.05f, Screen.height*0.5f));
	GUILayout.Box (weaponHeaterImage, GUILayout.Height (Screen.height*0.5f));

	GUILayout.EndArea();
	
	GUI.Box( Rect(Screen.width*0.5f-10 , Screen.height*0.5f - 10, 20,20 ), crossHair);
	*/
}

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
