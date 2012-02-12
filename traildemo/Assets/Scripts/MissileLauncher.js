var missile : GameObject;
var spawnPointLeft : Transform;
var spawnPointRight : Transform;

function Awake () {

	if (spawnPointLeft == null)
		spawnPointLeft = transform;

	if (spawnPointRight == null)
		spawnPointRight = transform;
}

function Update () {
	
	/* TODO: will enable it when testing it on real device
	// Left stick
	if (Input.GetMouseButtonDown (0))
	{
		//var position : Vector3 = new Vector3(0, -0.2, 1) * 1.0;
		//position = transform.TransformPoint (position);
		var leftMissile : GameObject = Instantiate (missile, spawnPointLeft.position, transform.rotation) as GameObject;
		Physics.IgnoreCollision(leftMissile.collider, collider);
	}
	*/
	// Right stick
	if (Input.GetMouseButtonDown (1))
	{
		//var position : Vector3 = new Vector3(0, -0.2, 1) * 1.0;
		//position = transform.TransformPoint (position);
		var rightMissile : GameObject = Instantiate (missile, spawnPointRight.position, transform.rotation) as GameObject;
		Physics.IgnoreCollision(rightMissile.collider, collider);
	}
}
