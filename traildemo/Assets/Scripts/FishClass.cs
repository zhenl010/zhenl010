using UnityEngine;
using System.Collections;

public class FishClass : MonoBehaviour {
	
	public float speed = 10f;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
		if (transform.position.x < -65 || transform.position.x > 65) {
			//turn around
			transform.Rotate(new Vector3(0, 180, 0));
			//transform.Translate( new Vector3(0, 0, 0) );
 
			//get new speed
			speed = Random.Range(10f,20f);
		}
		transform.Translate( new Vector3(-speed*Time.deltaTime,0,0) );
		
		//Debug.Log("Output from FishClass");
	}
}
