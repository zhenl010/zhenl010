#pragma strict


//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
// AiCore

//--------------------------------------------------------------
// Static Data
enum AiState { Idle, Loco, Attack, Pain, Death, Count }
var stateTransitionFunctions : Function[];
var stateActionFunctions : Function[];

//--------------------------------------------------------------
// Public Data
var aiGameObject : GameObject;
var deathEeffects : GameObject;
var locoSpeed : float;  

//--------------------------------------------------------------
// Private Data
private var m_currentState : AiState;
private var m_stateTimer : float;
private var m_gotPain: boolean;
private var m_shouldDie: boolean;


//**************************************************************
//**************************************************************
function Start () {
	//Debug.Log("AiCore start");
	
	m_currentState = AiState.Idle;
	m_stateTimer = 0f;
	m_gotPain = false;
	m_shouldDie = false;
	
	// initial state transition checking funtions
	stateTransitionFunctions = new Function[AiState.Count];
	stateTransitionFunctions[AiState.Idle] =  _IdleTransition;	
	stateTransitionFunctions[AiState.Loco] =  _LocoTransition;	
	stateTransitionFunctions[AiState.Attack] =  _AttackTransition;	
	stateTransitionFunctions[AiState.Pain] =  _PainTransition;	
	stateTransitionFunctions[AiState.Death] =  _DeathTransition;	

	// initial state action performing funtions
	stateActionFunctions = new Function[AiState.Count];
	stateActionFunctions[AiState.Idle] =  _IdleAction;	
	stateActionFunctions[AiState.Loco] =  _LocoAction;	
	stateActionFunctions[AiState.Attack] =  _AttackAction;	
	stateActionFunctions[AiState.Pain] =  _PainAction;	
	stateActionFunctions[AiState.Death] =  _DeathAction;	

}

//--------------------------------------------------------------

function Update () {
	//Debug.Log("AiCore Update");

	// check transitions
	if(_CheckTransition()){
		//transit to new state:
		m_stateTimer = 0f;	
	}else{
		m_stateTimer += Time.deltaTime;
	}
	
	// doing the current state action
	_PerformAction();
}

//**************************************************************

function _CheckTransition (): boolean {

	return stateTransitionFunctions[m_currentState]();
}

//--------------------------------------------------------------
function _IdleTransition (): boolean {
	
	if (m_shouldDie){
		m_currentState = AiState.Death;
		return true;
	}	
	if(m_gotPain) {
		m_currentState = AiState.Pain;
		return true;
	}	
			
	/*
	if(m_stateTimer > 5f){
		m_currentState = AiState.Loco;
		return true;
	}
	
	return false;

	*/
	m_currentState = AiState.Loco;
	return true;

}

//--------------------------------------------------------------
function _LocoTransition () : boolean{

	if (m_shouldDie){
		m_currentState = AiState.Death;
		return true;
	}	
	if(m_gotPain) {
		m_currentState = AiState.Pain;
		return true;
	}	

	/*
	if(m_stateTimer > 5f){
		m_currentState = AiState.Idle;
		return true;
	}
	*/
	return false;
	
}

//--------------------------------------------------------------
function _AttackTransition (): boolean {

	var result : boolean = false;
	return result;
	
}

//--------------------------------------------------------------
function _PainTransition () : boolean{
	
	if(m_stateTimer > 1f){
		m_currentState = AiState.Idle;
		return true;
	}	
	return false;	
}

//--------------------------------------------------------------
function _DeathTransition () : boolean{
	return false;
}

//**************************************************************

function _PerformAction () {
	stateActionFunctions[m_currentState]();
}

//--------------------------------------------------------------
function _IdleAction () {
	
}

//--------------------------------------------------------------
function _LocoAction () {
	/*
	if ( m_stateTimer > 5f) {
		
		//get new speed
		locoSpeed = Random.Range(1f,2f);
	}
	*/

	//transform.RotateAround (Vector3.zero, Vector3.up, locoSpeed * Time.deltaTime);
	//transform.Translate( new Vector3(-locoSpeed*Time.deltaTime,0,0) );
}
//--------------------------------------------------------------
function _AttackAction () {
	
}
//--------------------------------------------------------------
function _PainAction () {
	
}
//--------------------------------------------------------------
function _DeathAction () {
	Debug.Log("Shark death action");
	if (aiGameObject) {
		Spawner.Destroy (aiGameObject);	
		
	}
	if ( deathEeffects)
		Spawner.Spawn (deathEeffects, transform.position, transform.rotation);
}

//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
// callback function from signals

function OnPain () {
	m_gotPain = true; 
}

function OnDie () {
	m_shouldDie = true; 
}
