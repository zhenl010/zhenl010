//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
// public data
public var mainBGImage : Texture2D;


//**************************************************************
//**************************************************************
// code for making transparent texture
/*
// case 0
function Start(){
  	transform.position = Vector3(0.5, 0.5, 0); // ensure screen centered
  	var r = Rect(-Screen.width/2, -Screen.height/2, Screen.width, Screen.height);
  	guiTexture.pixelInset = r; // fill the whole screen
  	guiTexture.color.a = 0; // completely transparent at Start
}




// case 1
function DrawBar(BarLeft:int, BarTop:int, BarTexture:Texture, MaxValue:float, Value:float)
{
    var LocationRect:Rect = Rect(BarLeft,BarTop,EmptybarTexture.width,EmptybarTexture.height);
    var DrawRect:Rect = Rect(0,0,EmptybarTexture.width,EmptybarTexture.height);
    var DrawWidth:int;

    DrawWidth = EmptybarTexture.width*(Value/MaxValue);
    GUI.BeginGroup (LocationRect);
        GUI.DrawTexture (DrawRect, EmptybarTexture);
        GUI.BeginGroup (new Rect (0, 0, DrawWidth, EmptybarTexture.height));
            GUI.DrawTexture(DrawRect, BarTexture);
        GUI.EndGroup ();
        GUI.Label(Rect((DrawRect.width/2)-10,-5,40,50),Value.ToString());
    GUI.EndGroup ();
}


You need to add the following to the top of your script, then drag the textures you want to use into these objects in the inspector.

var EmptybarTexture:Texture2D; var HealthbarTexture:Texture2D;

After you have these at the top, and the textures you want to use assigned, it should work just fine.

Use the following to draw the bar... DrawBar(0,0,HealthbarTexture,100,50);

Hope this helps, -Larry
*/
//
function OnGUI () {

	// Weapon Heater
	//GUILayout.BeginArea(Rect(0,0,Screen.width, Screen.height));
	//GUILayout.Box ( mainBGImage, GUILayout.Width(Screen.width), GUILayout.Height(Screen.height));
	
	GUILayout.BeginArea(Rect(Screen.width*0.5f-50f, Screen.height*0.5f -50, 100, 100 ));
	
	if (GUILayout.Button ("Start Game")) {
		Application.LoadLevel ("LevelScene");
	}

	// Make the second button.
	//if (GUILayout.Button ("Level 2")) {
	//	Application.LoadLevel ("");
	//}
	//GUILayout.EndArea();
	GUILayout.EndArea();
	
	
}

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
