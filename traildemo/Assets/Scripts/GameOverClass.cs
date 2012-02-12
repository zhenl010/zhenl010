using UnityEngine;
using System.Collections;

public class GameOverClass : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.anyKeyDown){
			PlayerClass.score = 0;
			Application.LoadLevel("LevelScene");
		}
	}
}
