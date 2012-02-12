//////////////////////////////////////////////////////////////
// PlayerRelativeControl.js
// Penelope iPhone Tutorial
//
// PlayerRelativeControl creates a control scheme similar to what
// might be found in a 3rd person, over-the-shoulder game found on
// consoles. The left stick is used to move the character, and the
// right stick is used to rotate the character. A quick double-tap
// on the right joystick will make the character jump.
//////////////////////////////////////////////////////////////


var moveJoystick : Joystick;
var rotateJoystick : Joystick;

var cameraPivot : Transform;						// The transform used for camera rotation

var forwardSpeed : float = 4;
var backwardSpeed : float = 1;
var sidestepSpeed : float = 1;
var jumpSpeed : float = 8;
var inAirMultiplier : float = 0.25;					// Limiter for ground speed while jumping
var rotationSpeed : Vector2 = Vector2( 50, 25 );	// Camera rotation speed for each axis

private var thisTransform : Transform;
//private var character : CharacterController;
//private var animationController : AnimationController;
private var cameraVelocity : Vector3;
public var velocity : float;						// Used for continuing momentum while in air

function Start()
{
	// Cache component lookup at startup instead of doing this every frame		
	thisTransform = GetComponent( Transform );
	/*
	character = GetComponent( CharacterController );	
	animationController = GetComponent( AnimationController );
	
	// Set the maximum speeds, so that the animation speed adjustment works	
	animationController.maxForwardSpeed = forwardSpeed;	
	animationController.maxBackwardSpeed = backwardSpeed;
	animationController.maxSidestepSpeed = sidestepSpeed;
	*/
	
	// Move the character to the correct start position in the level, if one exists
	var spawn = GameObject.Find( "PlayerSpawn" );
	if ( spawn )
		thisTransform.position = spawn.transform.position;
}

function OnEndGame()
{
	// Disable joystick when the game ends	
	moveJoystick.Disable();
	rotateJoystick.Disable();	

	// Don't allow any more control changes when the game ends
	this.enabled = false;
}

function Update()
{
	var movement = thisTransform.TransformDirection( Vector3( moveJoystick.position.x, 0, moveJoystick.position.y ) );

	// We only want horizontal movement
	movement.y = 0;
	movement.Normalize();

	var cameraTarget = Vector3.zero;

	// Apply movement from move joystick
	var absJoyPos = Vector2( Mathf.Abs( moveJoystick.position.x ), Mathf.Abs( moveJoystick.position.y ) );	
	if ( absJoyPos.y > absJoyPos.x )
	{
		if ( moveJoystick.position.y > 0 )
			movement *= forwardSpeed * absJoyPos.y;
		else
		{
			movement *= backwardSpeed * absJoyPos.y;
			cameraTarget.z = moveJoystick.position.y * 0.75;
		}
	}
	else
	{
		movement *= sidestepSpeed * absJoyPos.x;
		
		// Let's move the camera a bit, so the character isn't stuck under our thumb
		cameraTarget.x = -moveJoystick.position.x * 0.5;
	}
	
		
	movement *= velocity;	
	//movement += Physics.gravity;
	movement *= Time.deltaTime;
	
	// clear the y delta
	
	// Actually move the character	
	thisTransform.Translate( movement );
	//thisTransform.RotateAround (Vector3.zero, Vector3.up, velocity * Time.deltaTime);
	
	// Seek camera towards target position
	var pos = cameraPivot.localPosition;
	pos.x = Mathf.SmoothDamp( pos.x, cameraTarget.x, cameraVelocity.x, 0.3 );
	pos.z = Mathf.SmoothDamp( pos.z, cameraTarget.z, cameraVelocity.z, 0.5 );
	cameraPivot.localPosition = pos;

	// Apply rotation from rotation joystick
	var camRotation = rotateJoystick.position;
	camRotation.x *= rotationSpeed.x;
	camRotation.y *= rotationSpeed.y;
	camRotation *= Time.deltaTime;
	
	// Rotate the character around world-y using x-axis of joystick
	thisTransform.Rotate( 0, camRotation.x, 0, Space.World );
	
	// Rotate only the camera with y-axis input
	cameraPivot.Rotate( camRotation.y, 0, 0 );

}