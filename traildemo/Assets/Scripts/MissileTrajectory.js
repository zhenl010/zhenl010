var explosion : GameObject;

function FixedUpdate () {
	rigidbody.AddForce (transform.TransformDirection (Vector3.forward) * 200.0);
}

function OnCollisionEnter(collision : Collision) {
	var contact : ContactPoint = collision.contacts[0];
	var thisExplosion : GameObject = Instantiate (explosion, contact.point + (contact.normal * 1.0) , Quaternion.identity);
	
	if (collision.gameObject.tag == "enemy"){
		Destroy (collision.gameObject);
	}
	
	Destroy (thisExplosion, 2.0);
	Destroy (gameObject);
	
	//Debug.Log(collision.gameObject.name);
	if (collision.gameObject.name == "Shark"){
		
		// reset shark
		collision.gameObject.transform.rotation = Quaternion.identity;
		collision.gameObject.transform.position = new Vector3(50f, 60f, 80f);
	}
}
