var currentBlade : GameObject;
var currCamera : Camera;
var distanceToCamera : float = 2.0;

private var doFollowTouches : boolean = false;

function Start()
{
    currentBlade.SetActiveRecursively( false );

    if( !currCamera )
    {
        currCamera = Camera.main;
    }
}

function Update ()
{
    if( Input.GetMouseButtonDown(0) )
    {
       currentBlade.SetActiveRecursively( true );
       doFollowTouches = true;
    }

    if( doFollowTouches )
    {
        // Move the "targetObject" to where the mouse/touch was recorded in world space
        var posScreen : Vector3 = Vector3(Input.mousePosition.x, Input.mousePosition.y, distanceToCamera);
        var posWorld : Vector3 = currCamera.ScreenToWorldPoint(posScreen);
        var facingDirection : Vector3 = (posWorld - currCamera.transform.position).normalized;
        // currentBlade.position = Vector3(posWorld.x, posWorld.y, currentBlade.position.z);
        currentBlade.transform.position = posWorld;
        currentBlade.transform.forward = facingDirection;
    }

    if( Input.GetMouseButtonUp(0) )
    {
        currentBlade.SetActiveRecursively( false );
        doFollowTouches = false;
    }
}