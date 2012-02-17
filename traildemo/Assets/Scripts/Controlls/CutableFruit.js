var fruitParts : GameObject;
var partsLifeTime : float = 3.0;

function ReactToCut()
{
    Destroy(gameObject);

    var clone : GameObject;
    clone = Instantiate(fruitParts, transform.position, transform.rotation);
    clone.AddComponent( "SelfDestruct" );
    clone.GetComponent( "SelfDestruct" ).lifeTime = partsLifeTime;
}