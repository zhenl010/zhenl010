using UnityEngine;
using System.Collections;

[RequireComponent(typeof(GUITexture))]

// Private class
public class Boundary {
	public	Vector2 min;
	public	Vector2 max;
}

public class JoyStickClass : MonoBehaviour {
	
	private GUITexture gui;
	private Rect defaultRect;
	private Vector2 guiTouchOffset;
	private Boundary guiBoundary;	
	private Vector2 guiCenter;
	private int lastFingerId;
	private float tapTimeWindow;
	
	static private JoyStickClass[] joysticks; //= new ArrayList();  
	static private bool enumeratedJoysticks = false;
	static private float tapTimeDelta = 0.3f;
	
	public Vector2 position; // value between -1f and 1f, based on the movement of the joystick 
	public Vector2 deadZone; 
	public bool normalized;
	public int tapCount;
	
	// Use this for initialization
	void Start () {
		gui = GetComponent<GUITexture>();
		
		if(gui != null){
		
			// Get where the gui text was originally placed
			defaultRect = gui.pixelInset;
			
			// get our offset for center instead of corner
			guiTouchOffset.x = defaultRect.width * 0.5f;
			guiTouchOffset.y = defaultRect.height * 0.5f;
			
			//initialize the guiBoundray
			guiBoundary = new Boundary();
			guiBoundary.min.x = defaultRect.x - guiTouchOffset.x;
			guiBoundary.min.y = defaultRect.y - guiTouchOffset.y;
			guiBoundary.max.x = defaultRect.x + guiTouchOffset.x;
			guiBoundary.max.y = defaultRect.y + guiTouchOffset.y;
			
			// Initialize guiCenter
			guiCenter.x = defaultRect.x + guiTouchOffset.x;
			guiCenter.y = defaultRect.y + guiTouchOffset.y;
					
		}
		
		lastFingerId = -1;
	}
	
	// Update is called once per frame
	void Update () {
	
		Rect inset;
		Touch touch;
		int count = Input.touchCount;
		
		if(!enumeratedJoysticks){
			joysticks = FindObjectsOfType(typeof(JoyStickClass)) as JoyStickClass[];
			enumeratedJoysticks = true;
		}
		
		// Adjust the tap time window while it is still available
		if( tapTimeWindow > 0)
			tapTimeWindow -= Time.deltaTime;
		else
			tapCount =0;
		
		if( count ==0){
			Reset();
		} else	{
			for(int i = 0; i< count; i++){
				touch = Input.GetTouch(i);
				if(gui.HitTest(touch.position) && 
				   ( lastFingerId == -1 || lastFingerId != touch.fingerId) ){
					
					lastFingerId = touch.fingerId;
					
					// Accumulate taps if it is within the time window
					if(tapTimeWindow>0)
						tapCount ++;
					else{
						tapCount =1;
						tapTimeWindow = tapTimeDelta;
					}
					
					// logic for latching the fingers
					foreach(JoyStickClass joystick in joysticks){
						if (joystick != this){
							joystick.LatchedFinger(touch.fingerId);
						}
					}
				}
				
				if( lastFingerId == touch.fingerId){
					
					// Override the tap count with what the iPhone SDK reports if it is greater
					// This is a workaround, since the iPhone SDK does not currently track taps
					// for multiple touches
					if(touch.tapCount > tapCount)
						tapCount = touch.tapCount;					
					
					// Change the location of the joystick graphic to match where the touch is
					inset = gui.pixelInset;
					inset.x = Mathf.Clamp((touch.position-guiTouchOffset).x, guiBoundary.min.x, guiBoundary.max.x);
					inset.y = Mathf.Clamp((touch.position-guiTouchOffset).y, guiBoundary.min.y, guiBoundary.max.y);
					gui.pixelInset = inset;
					
					// Another check to see if fingers are touching
					if (touch.phase == TouchPhase.Ended || touch.phase == TouchPhase.Canceled){
						Reset();
					}
				}			
			}	
		}
		
		// setting up the position
		position.x = ( gui.pixelInset.x + guiTouchOffset.x - guiCenter.x) / guiTouchOffset.x;
		position.y = ( gui.pixelInset.y + guiTouchOffset.y - guiCenter.y) / guiTouchOffset.y;
		
		float absoluteX = Mathf.Abs(position.x);
		float absoluteY = Mathf.Abs(position.y);
		if( absoluteX < deadZone.x){
			position.x = 0f;
		} else if (normalized){
			position.x = Mathf.Sign(position.x) * (absoluteX - deadZone.x)/(1 - deadZone.x);
		}
		
		if( absoluteY < deadZone.y){
			position.y = 0f;
		} else if (normalized){
			position.y = Mathf.Sign(position.y) * (absoluteY - deadZone.y)/(1 - deadZone.y);
		}
	}
	
	// Reset the stick to default position
	void Reset(){
		if(gui != null)
			gui.pixelInset= defaultRect;
		lastFingerId = -1;
	}
	
	// latch finger
	void LatchedFinger (int fingerId){
		
		if(lastFingerId == fingerId){
			Reset();
		}
	}
	
	// Disable function
	void Disable(){
		gameObject.active = false;
		enumeratedJoysticks = false;
	}
}
