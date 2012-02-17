var animationTarget : Animation;
var maxForwardSpeed : float = 6;
var maxBackwardSpeed : float = 3;
var maxSidestepSpeed : float = 4;

private var isJumping : boolean = false;
private var isLanding : boolean = false;
private var minUpwardSpeed = 4.8;
private var minLandingSpeed = -1.5;

private var thisTransform : Transform;
private var charController : CharacterController;

function Start()
{
    charController = GetComponent(CharacterController);
    // thisTransform = GetComponent( Transform );
    thisTransform = transform;

    animationTarget.wrapMode = WrapMode.Loop;
    animationTarget["idle"].wrapMode = WrapMode.Loop;
    animationTarget["walk"].wrapMode = WrapMode.Loop;
    animationTarget["run"].wrapMode = WrapMode.Loop;
    animationTarget["charge"].wrapMode = WrapMode.ClampForever;
}

function OnEndGame()
{
    this.enabled = false;
}

function Update()
{
    var characterVelocity = charController.velocity;
    var horizontalVelocity = characterVelocity;
    horizontalVelocity.y = 0;

    var speed = horizontalVelocity.magnitude;
    var upwardsMotion = Vector3.Dot(thisTransform.up, characterVelocity);

    if(!charController.isGrounded && upwardsMotion > minUpwardSpeed)
    {
        isJumping = true;
    }
    if(charController.isGrounded && upwardsMotion < minLandingSpeed)
    {
        isLanding = true;
    }

    if(animationTarget.IsPlaying("run-land") &&
       animationTarget["run-land"].normalizedTime < 1.0 &&
       speed > 0.0)
    {
        // ...
    }
    else if(animationTarget.IsPlaying("jump-land"))
    {
        // Let animation finish then go back to idle
        if(animationTarget["jump-land"].normalizedTime >= 1.0)
        {
            animationTarget.Play("idle");
        }
    }
    else if(animationTarget.IsPlaying("jump") &&
       animationTarget["jump"].normalizedTime < 1.0 &&
       upwardsMotion > 0.0)
    {
        // Let jump animation finish
    }
    else if(isJumping)
    {
        // Jumping stops with a landing ....
        if(isLanding)
        {
            // Debug.Log("Landing !!!");

            if(speed > 0)
            {
                animationTarget.Play("run-land");
            }
            else
            {
                animationTarget.Play("jump-land");
            }
            isJumping = false;
        }
        else
        {
            // Jump animation to start
            if(upwardsMotion > minUpwardSpeed)
            {
                animationTarget.Play("jump");
            }
        }
    }
    else if(speed > 0)
    {
        // Use the largest movement direction to determine which animations to play
        var forwardMotion = Vector3.Dot(thisTransform.forward, horizontalVelocity);
        var sidewaysMotion = Vector3.Dot(thisTransform.right, horizontalVelocity);
    
        var t = 0.0;
    
        if(Mathf.Abs(forwardMotion) > Mathf.Abs(sidewaysMotion))
        {
            // forward or backward motion major
            if(forwardMotion > 0.0)
            {
                t = Mathf.Clamp(Mathf.Abs(speed/maxForwardSpeed),0, maxForwardSpeed);
                animationTarget["run"].speed = Mathf.Lerp(0.25,1,t);
                if(animationTarget.IsPlaying("walk") || animationTarget.IsPlaying("idle"))
                {
                    animationTarget.Play("run");
                }
                else
                {
                    animationTarget.CrossFade("run");
                }
            }
            else
            {
                t = Mathf.Clamp(Mathf.Abs(speed/maxBackwardSpeed), 0, maxBackwardSpeed);
                animationTarget["run"].speed = Mathf.Lerp(0.25,1,t);
                animationTarget.CrossFade("run");
            }
        }
        else
        {
            // sideway motion major
            t = Mathf.Clamp(Mathf.Abs(speed/maxSidestepSpeed),0,maxSidestepSpeed);
            if(sidewaysMotion > 0)
            {
                animationTarget["run"].speed = Mathf.Lerp(0.25,1,t);
                animationTarget.CrossFade("run");
            }
            else
            {
                animationTarget["run"].speed = Mathf.Lerp(0.25,1,t);
                animationTarget.CrossFade("run");
            }
        }
    }
    else
    {
        // idling ...
        animationTarget.CrossFade("idle");
    }
}