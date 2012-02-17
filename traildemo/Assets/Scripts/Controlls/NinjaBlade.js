function OnTriggerEnter( inCollider : Collider )
{
    // cut into sth? 1 is the type of the blade 
    inCollider.SendMessage( "ReactToCut", 1, SendMessageOptions.DontRequireReceiver );
}