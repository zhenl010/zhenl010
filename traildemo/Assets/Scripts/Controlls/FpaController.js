////////////////////////////////////////////////////////////////
// Very naive camera based player moveDirection control:
// Left stick moves the charController
// Right stick rotates the camera
////////////////////////////////////////////////////////////////
@script RequireComponent( CharacterController )

var cameraTransform : Transform;
var cameraPivot : Transform;
var rotationSpeed : Vector2 = Vector2(50, 25);
var walkSpeed : float = 0.06;
var jumpSpeed : float = 2.0;
var gravity : float = (-10.0);
var dampingFactor : float = 0.96;

private var thisTransform : Transform;
private var charController : CharacterController;
private var moveSpeed : Vector3 = Vector3.zero;

function Start()
{
    thisTransform = GetComponent( Transform );
    var spawn = GameObject.Find("PlayerSpawn");
    if(spawn)
    {
        thisTransform.position = spawn.transform.position;
    }

    charController = GetComponent( CharacterController );
}

function FaceMovementDirection()
{
    var horizontalVelocity : Vector3 = charController.velocity;
    horizontalVelocity.y = 0.0;
    if(horizontalVelocity.magnitude > 0.01)
    {
        thisTransform.forward = horizontalVelocity.normalized;
    }
}

function Update ()
{
    if(charController.isGrounded)
    {
        if( Mathf.Abs(Input.GetAxis("Vertical"))>0.01 || Mathf.Abs(Input.GetAxis("Horizontal"))>0.01 )
        {
            // print("We are grounded");
            var moveDirection : Vector3 = Vector3(Input.GetAxis("Horizontal"),
                                                                            0,
                                                    Input.GetAxis("Vertical"));
            moveDirection = cameraTransform.TransformDirection(moveDirection);

            moveDirection.y = 0.0;
            moveDirection.Normalize();
            moveSpeed = moveDirection * walkSpeed;
        }
        else
        {
            // explicitly make the speed zero
            moveSpeed = Vector3.zero;
        }

        // constant jump speed upward, which is positive y-axis
        if(Input.GetButton("Jump"))
        {
            moveSpeed.y = jumpSpeed;
        }
    }
    else
    {
        // print("ON AIR!!!!!!!!!!!!!!!!!!!!");
        // Debug.Break();
    }

    // Move the controller
    charController.Move(moveSpeed * Time.deltaTime);

    // Let character face the direction he/she is moving into
    // FaceMovementDirection();

    // Apply gravity
    moveSpeed.y = moveSpeed.y + gravity * Time.deltaTime;
    // moveSpeed.y += Physics.gravity.y * Time.deltaTime;
    moveSpeed *= dampingFactor;

    // Camera rotation responding to input
    var camRotation : Vector3 = Vector3.zero;
    if (Input.GetKeyDown("[6]"))
    {
        camRotation.x += rotationSpeed.x;
    }
    else if (Input.GetKeyDown("[4]"))
    {
        camRotation.x -= rotationSpeed.x;
    }

    if (Input.GetKeyDown("[8]"))
    {
        camRotation.y += rotationSpeed.y;
    }
    else if (Input.GetKeyDown("[2]"))
    {
        camRotation.y -= rotationSpeed.y;
    }
    camRotation *= Time.deltaTime;
    cameraPivot.Rotate(0, camRotation.x, 0, Space.World);
    cameraPivot.Rotate(camRotation.y, 0, 0);
}

function OnEndGame()
{
    this.enabled = false;
}