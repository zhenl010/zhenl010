#pragma strict

var material : Material;
var maxWidth : float = 0.025;
var lifeTime : float = 0.16;

class HermiteBasis extends System.ValueType
{
    var tX : float;
    var h00 : float;
    var h10 : float;
    var h01 : float;
    var h11 : float;

    public function HermiteBasis(t:float)
    {
        this.tX = t;
        var t2:float = t*t;
        var t3:float = t2*t;

        this.h00 = 2.0*t3-3.0*t2+1.0;
        this.h10 = t3-2.0*t2+t;
        this.h01 = -2.0*t3+3.0*t2;
        this.h11 = t3-t2;
    }
}

class CardinalPoint extends System.ValueType
{
    var vexLp : Vector3;
    var vexRp : Vector3;
    var vexLm : Vector3;
    var vexRm : Vector3;
}

static private var GAME_FPS : int = 120;
static private var insertHermites : HermiteBasis[];
static private var insertVexNum : int = 4;

private var maxPointNum : int;
private var vexNum : int;
private var currCamera : Camera;
private var trailPoints : Vector3[];
private var prevPerps : Vector3[];
private var vexPoints : CardinalPoint[];
private var headIdx : int;
private var tailIdx : int;
private var lastMove : Vector3;
private var trailLength : float;
private var trailWidth : float;
private var minVexMove : float;
private var widthDec : float;

private var trailObject : GameObject;
private var bladeMesh : Mesh;
private var bladeVertices : Vector3[];
private var bladeUV : Vector2[];
private var bladeTriangles : int[];
private var doRestartTrail : boolean;

function Awake()
{
    // Init private variables
    maxPointNum = GAME_FPS * lifeTime;

    insertHermites = new HermiteBasis[insertVexNum];
    for(var i:int=0; i<insertVexNum; ++i)
    {
        insertHermites[i] = HermiteBasis((1.0+i)/(insertVexNum+1));
    }
}

function Start()
{
    // Remember current camera as reference
    if( !currCamera )
    {
        currCamera = Camera.main;
    }

    // Pixel accuracy
    var distanceToCamera : float = (transform.position - currCamera.transform.position).magnitude;
    var posWorld : Vector3 = currCamera.ScreenToWorldPoint(
                                Vector3( Screen.width/2, Screen.height/2, distanceToCamera));
    minVexMove = (posWorld - currCamera.ScreenToWorldPoint(
                 Vector3( Screen.width/2+1, Screen.height/2+1, distanceToCamera))).magnitude;
    widthDec = maxWidth / maxPointNum;
}

function OnEnable()
{
    trailPoints = new Vector3[ maxPointNum ];
    prevPerps = new Vector3[ maxPointNum ];
    vexPoints = new CardinalPoint[maxPointNum];
    trailLength = 0.0;
    trailWidth = 0.0;
    doRestartTrail = true;

    InitTrailTriangles();

    if(!trailObject)
    {
        AttachTailObject();
    }
}

function OnDisable()
{
    Destroy(trailObject);
}

function Update()
{
    if( doRestartTrail )
    {
        RestartTrail();
        doRestartTrail = false;
    }
    else
    {
        var moveVector : Vector3 = transform.position - trailPoints[headIdx];
        lastMove = moveVector.normalized;

        if(moveVector.magnitude > minVexMove)
        {
            var vectorToCamera : Vector3 = currCamera.transform.position - transform.position;
            var perpendicular : Vector3 = Vector3.Cross(lastMove, vectorToCamera).normalized;
    
            var obslIdx : int = (tailIdx + maxPointNum - 1) % maxPointNum;
            var obslVector : Vector3 = trailPoints[tailIdx] - trailPoints[obslIdx];
            trailLength = trailLength + moveVector.magnitude - obslVector.magnitude;
            trailWidth = Mathf.Min(maxWidth, trailWidth + moveVector.magnitude);

            headIdx = tailIdx;
            tailIdx = PrevIdx(tailIdx);
            trailPoints[headIdx] = transform.position;
            prevPerps[headIdx] = perpendicular;
        }

        UpdateTrailMesh();

        trailWidth = trailWidth - widthDec;
        if( trailWidth < 0.0 ) // disappeared trail
        {
            trailWidth = 0.0;
            doRestartTrail = true;
        }
    }
}

private function AttachTailObject()
{
    trailObject = new GameObject( "Trail" );
    trailObject.transform.parent = null;
    trailObject.transform.position = Vector3.zero;
    trailObject.transform.rotation = Quaternion.identity;
    trailObject.transform.localScale = Vector3.one;
    trailObject.AddComponent(MeshFilter);
    trailObject.AddComponent(MeshRenderer);
    trailObject.renderer.material = material;

    bladeMesh = new Mesh();
    trailObject.GetComponent(MeshFilter).mesh.Clear();
    trailObject.GetComponent(MeshFilter).mesh = bladeMesh;
    bladeMesh.vertices = bladeVertices;
    bladeMesh.uv = bladeUV;
    bladeMesh.triangles = bladeTriangles;
}

private function InitTrailTriangles()
{
    var i:int;
    vexNum = 2*(maxPointNum+(maxPointNum-1)*insertVexNum);
    bladeVertices = new Vector3[ vexNum ];

    bladeUV = new Vector2[ vexNum ];
    var uvInc : float = 2.0 / vexNum;
    var uvTailY : float = 1.0;
    for(i=0; i<(vexNum/2); ++i)
    {
        bladeUV[2*i+0] = Vector2(0.0, uvTailY);
        bladeUV[2*i+1] = Vector2(1.0, uvTailY);
        uvTailY = uvTailY - uvInc;
    }

    var triangleNum : int = 2*((vexNum/2)-1);
    bladeTriangles = new int[ 3*triangleNum ];
    // Init triangles
    var itri:int = 0;
    for(i=1; i<(vexNum/2); ++i)
    {
        bladeTriangles[3*itri+0] = 2*i-1;
        bladeTriangles[3*itri+1] = 2*i-2;
        bladeTriangles[3*itri+2] = 2*i+1;
        ++itri;
        bladeTriangles[3*itri+0] = 2*i-2;
        bladeTriangles[3*itri+1] = 2*i+0;
        bladeTriangles[3*itri+2] = 2*i+1;
        ++itri;
    }

    // Init trail points
    for( i = 0; i < maxPointNum; ++i )
    {
        trailPoints[i] = transform.position;
    }
    headIdx = 0;
    tailIdx = maxPointNum - 1;
    trailLength = 0.0;
}

private function RestartTrail()
{
    var i : int;
    for( i = 0; i < maxPointNum; ++i )
    {
        trailPoints[i] = transform.position;
    }

    headIdx = 0;
    tailIdx = maxPointNum - 1;
    trailLength = 0.0;

    for( i = 0; i < vexNum; ++i)
    {
        bladeVertices[i] = transform.position;
    }
    bladeMesh.vertices = bladeVertices;
}

private function UpdateTrailMesh()
{
    var currIdx : int = headIdx;
    var nextIdx : int = NextIdx(currIdx);
    vexPoints[currIdx].vexLp = trailPoints[currIdx] + prevPerps[currIdx] * trailWidth;
    vexPoints[currIdx].vexRp = trailPoints[currIdx] - prevPerps[currIdx] * trailWidth;
    var vexLprev : Vector3 = vexPoints[currIdx].vexLp;
    var vexRprev : Vector3 = vexPoints[currIdx].vexRp;
    var vexLnext : Vector3 = trailPoints[nextIdx] + prevPerps[nextIdx] * trailWidth;
    var vexRnext : Vector3 = trailPoints[nextIdx] - prevPerps[nextIdx] * trailWidth;
    // on sided difference at the head point
    vexPoints[currIdx].vexLm = 0.5 * (vexLnext-vexLprev);
    vexPoints[currIdx].vexRm = 0.5 * (vexRnext-vexRprev);
    while (currIdx != tailIdx)
    {
        vexLprev = vexPoints[currIdx].vexLp;
        vexRprev = vexPoints[currIdx].vexRp;

        currIdx = nextIdx;
        nextIdx = NextIdx(currIdx);

        vexPoints[currIdx].vexLp = vexLnext;
        vexPoints[currIdx].vexRp = vexRnext;

        vexLnext = trailPoints[nextIdx] + prevPerps[nextIdx] * trailWidth;
        vexRnext = trailPoints[nextIdx] - prevPerps[nextIdx] * trailWidth;

        vexPoints[currIdx].vexLm = 0.5 * (vexLnext-vexLprev);
        vexPoints[currIdx].vexRm = 0.5 * (vexRnext-vexRprev);
    }
    // on sided difference at the tail point
    vexPoints[tailIdx].vexLm = 0.5 * (vexPoints[tailIdx].vexLp-vexPoints[currIdx].vexLp);
    vexPoints[tailIdx].vexRm = 0.5 * (vexPoints[tailIdx].vexRp-vexPoints[currIdx].vexRp);

    // Local variables...
    var ibv : int = 0;
    var xLength : float = 0.0;
    currIdx = headIdx;
    nextIdx = NextIdx(currIdx);
    var xDelta : float = (trailPoints[nextIdx] - trailPoints[currIdx]).magnitude;
    while (currIdx != tailIdx)
    {
        bladeVertices[ibv] = vexPoints[currIdx].vexLp;
        bladeUV[ibv] = Vector2(0.0, 1.0-xLength/trailLength);
        ++ibv;
        bladeVertices[ibv] = vexPoints[currIdx].vexRp;
        bladeUV[ibv] = Vector2(1.0, 1.0-xLength/trailLength);
        ++ibv;

        var deltaXkL : Vector3 = vexPoints[nextIdx].vexLp - vexPoints[currIdx].vexLp;
        var deltaXkR : Vector3 = vexPoints[nextIdx].vexRp - vexPoints[currIdx].vexRp;
        for(var iInsert:int=0; iInsert<insertVexNum; ++iInsert)
        {
            bladeVertices[ibv] = CubicHermite( insertHermites[iInsert]
                                                , vexPoints[currIdx].vexLp, vexPoints[currIdx].vexLm
                                                , vexPoints[nextIdx].vexLp, vexPoints[nextIdx].vexLm);
            bladeUV[ibv] = Vector2(0.0, 1.0-(xLength+xDelta*insertHermites[iInsert].tX)/trailLength);
            ++ibv;
            bladeVertices[ibv] = CubicHermite( insertHermites[iInsert]
                                                , vexPoints[currIdx].vexRp, vexPoints[currIdx].vexRm
                                                , vexPoints[nextIdx].vexRp, vexPoints[nextIdx].vexRm);
            bladeUV[ibv] = Vector2(1.0, 1.0-(xLength+xDelta*insertHermites[iInsert].tX)/trailLength);
            ++ibv;
        }

        currIdx = nextIdx;
        nextIdx = NextIdx(currIdx);
        xLength += xDelta;
        xDelta = (trailPoints[nextIdx] - trailPoints[currIdx]).magnitude;
    }
    bladeVertices[ibv++] = vexPoints[tailIdx].vexLp;
    bladeVertices[ibv++] = vexPoints[tailIdx].vexRp;

    // @TODO: only do mesh reset when necessary...
    bladeMesh = trailObject.GetComponent(MeshFilter).mesh;
    bladeMesh.Clear();
    bladeMesh.vertices = bladeVertices;
    bladeMesh.uv = bladeUV;
    bladeMesh.triangles = bladeTriangles;
}

private function PrevIdx(curIdx:int) : int
{
    return (curIdx + maxPointNum - 1) % maxPointNum;
}

private function NextIdx(curIdx:int) : int
{
    return (curIdx + 1) % maxPointNum;
}

private function CubicHermite( hBasis:HermiteBasis
                             , pt0:Vector3, mt0:Vector3
                             , pt1:Vector3, mt1:Vector3) : Vector3
{
    return hBasis.h00*pt0 + hBasis.h10*mt0 + hBasis.h01*pt1 + hBasis.h11*mt1;
}