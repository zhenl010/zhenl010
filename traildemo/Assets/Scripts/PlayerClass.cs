using UnityEngine;
using System.Collections;

public class PlayerClass : MonoBehaviour {
	//add the properties
	public GameObject mainCamera;
	//public GameObject gameBackground;
	public float nextZ = 0;
 
	public float speed;
	public GameObject bombPrefab;
	public static int score = 0;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {

		if(transform.position.x > 18)
		{
			speed = Random.Range(8f, 12f);
			transform.position = new Vector3(-18f, transform.position.y, transform.position.z);
		}
		transform.Translate(0, 0, speed * Time.deltaTime);	
		
		// instance the bomb
		if( Input.anyKeyDown){
			
			GameObject bombObject = (GameObject) Instantiate(bombPrefab);
			bombObject.transform.position = this.gameObject.transform.position;
			BombClass bomb = (BombClass)bombObject.GetComponent("BombClass");
			bomb.player = this;
		}
		
		//at the end of the Update method
		/*
		if (nextZ > mainCamera.transform.position.z) {
			mainCamera.gameObject.transform.Translate( 
				3* Mathf.Sin(transform.position.z/2 ) * Time.deltaTime, 
				0, 
				-Mathf.Sin(transform.position.z /2 ) * Time.deltaTime *0.3f
			);
			mainCamera.gameObject.transform.RotateAroundLocal( Vector3.up, Time.deltaTime*0.1f );
			// gameBackground.gameObject.transform.RotateAroundLocal( Vector3.up, Time.deltaTime*0.1f );
		}
		*/		
	}
		
	public void updateScoreBy (int deltaScore){
		PlayerClass.score += deltaScore;
		if(PlayerClass.score >3){
			Application.LoadLevel("WinScene");
		} else if ( PlayerClass.score < -3){
			Application.LoadLevel("LooseScene");
		}
		
		//at the end of the updateScoreBy method
		if (PlayerClass.score>0) {
			nextZ = PlayerClass.score*2.5f;
		}
	}
	
	void OnGUI(){
		GUIStyle style = new GUIStyle();
		style.fontSize = 20;
		GUI.Label(new Rect(10f, 10f, 100f, 20), "Score:" + PlayerClass.score, style);
	}
}
