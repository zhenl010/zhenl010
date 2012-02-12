//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
// data
private var gui : GUITexture;								// crosshair graphic

//**************************************************************
//**************************************************************
function Start()
{
	// Cache this component at startup instead of looking up every frame	
	gui = GetComponent( GUITexture );

	gui.pixelInset.height = Screen.height*0.05;
	gui.pixelInset.width = Screen.width*0.05;
	gui.pixelInset.x = (Screen.width - gui.pixelInset.width)*0.5;
	gui.pixelInset.y = (Screen.height - gui.pixelInset.height)*0.5;
	
}

//
function OnGUI () {
	// FEI_TODO: will remove it after deploying it to iphone
	gui.pixelInset.height = Screen.height*0.05;
	gui.pixelInset.width = Screen.width*0.05;
	gui.pixelInset.x = 0;//(Screen.width - gui.pixelInset.width)*0.5;
	gui.pixelInset.y = 0;//(Screen.height - gui.pixelInset.height)*0.5;

}

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
