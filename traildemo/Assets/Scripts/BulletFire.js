#pragma strict

private var state : boolean = false;
private var bulletAutoFire : AutoFire;

function Awake () {
	bulletAutoFire =  gameObject.GetComponent(AutoFire);	
}
		
function Update () {
	
	// mid mouse 
	if (state == false && Input.GetMouseButtonDown (2)) {
		bulletAutoFire.OnStartFire();
		state = true;
	}	
	else if (state == true && Input.GetMouseButtonUp (2)) {
		bulletAutoFire.OnStopFire();
		state = false;
	}
}
