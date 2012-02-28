// Undirectional graph path problem
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

struct Edge;
struct Vertex;
struct NborViaEdge
{
    NborViaEdge() {}
    NborViaEdge(Vertex* nbor) : nbor_(nbor) {}
    Vertex* nbor_;
};

struct Vertex
{
    Vertex() {}
    Vertex(int x, int y) : x_(x), y_(y) {}

    int x_;
    int y_;
    std::vector<NborViaEdge> nbors_;
    int cid_; // associate data

    bool operator==(const Vertex& rho) const
    {
        return this->x_ == rho.x_ && this->y_ == rho.y_;
    }
    bool operator!=(const Vertex& rho) const
    {
        return !(*this == rho);
    }
};

struct Edge
{
    Edge() {}
    Edge(Vertex* p1, Vertex* p2) { ends_[0] = p1; ends_[1] = p2; }

    Vertex* ends_[2];
};

// assuming "static" connected graph of bidirectional edges of same weight
struct ConnectedGraph
{
    // vertices with info of each vertex's nbors (thus edges)
    std::vector<Vertex> vertices_;

    int GetPenLiftNum();
};

int ConnectedGraph::GetPenLiftNum()
{
    using namespace std;

    int oddVexNum = 0;
    for (vector<Vertex>::iterator itov=vertices_.begin(); itov!=vertices_.end(); ++itov)
    {
        if ( (*itov).nbors_.size() % 2 == 1 )
        {
            ++oddVexNum;
        }
    }

    return oddVexNum>2 ? oddVexNum/2-1 : 0;
}

struct IntVector2
{
    IntVector2(int x, int y) : x_(x), y_(y) {}
    int x_;
    int y_;

    bool operator==(const IntVector2& rho) const
    {
        return this->x_ == rho.x_ && this->y_ == rho.y_;
    }
    bool operator!=(const IntVector2& rho) const
    {
        return !(*this == rho);
    }
};

struct RawEdge
{
    RawEdge() {}
    RawEdge(int x1, int y1, int x2, int y2) : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}
    int x1_;
    int y1_;
    int x2_;
    int y2_;

    bool InY() const { return x1_ == x2_; }
    bool InX() const { return y1_ == y2_; }
};

bool HasOverlap(const RawEdge& segOne, const RawEdge& segTwo)
{
    if ( segOne.InY() && segTwo.InY() && segOne.x1_ == segTwo.x1_ ) // overlap in y
    {
        if (segOne.y1_ < segOne.y2_)
        {
            return !( (segTwo.y1_ < segOne.y1_ && segTwo.y2_ < segOne.y1_) || (segOne.y2_ < segTwo.y1_ && segOne.y2_ < segTwo.y2_) );
        } 
        else
        {
            return !( (segOne.y1_ < segTwo.y1_ && segOne.y1_ < segTwo.y2_) || (segTwo.y1_ < segOne.y2_ && segTwo.y2_ < segOne.y2_) );
        }
    } 
    else if ( segOne.InX() && segTwo.InX() && segOne.y1_ == segTwo.y1_ ) // overlap in x
    {
        if (segOne.x1_ < segOne.x2_)
        {
            return !( (segTwo.x1_ < segOne.x1_ && segTwo.x2_ < segOne.x1_) || (segOne.x2_ < segTwo.x1_ && segOne.x2_ < segTwo.x2_) );
        } 
        else
        {
            return !( (segOne.x1_ < segTwo.x1_ && segOne.x1_ < segTwo.x2_) || (segTwo.x1_ < segOne.x2_ && segTwo.x2_ < segOne.x2_) );
        }
    }
    else
    {
        return false;
    }
}

// Assume caller's responsibility to assure segX parallel to x-axis and segY parallel to y-axis
// segX.x1_ < segX.x2_ and segY.y1_ < segY.y2_
inline bool DoIntersectHardToSplitY(const RawEdge& segX, const RawEdge& segY)
{
    // the possible intersect point with input assumption:
    return (segX.x1_ <= segY.x1_ && segY.x1_ <= segX.x2_) && (segY.y1_ < segX.y1_ && segX.y1_ < segY.y2_);
}
inline bool DoIntersectHardToSplitX(const RawEdge& segX, const RawEdge& segY)
{
    // the possible intersect point with input assumption:
    return ( (segX.x1_ < segY.x1_ && segY.x1_ < segX.x2_) && (segY.y1_ <= segX.y1_ && segX.y1_ <= segY.y2_) );
}

RawEdge MergeOverlap(const RawEdge& segOne, const RawEdge& segTwo)
{
    using namespace std;
    if ( segOne.InY() && segTwo.InY() && segOne.x1_ == segTwo.x1_ ) // overlap in y
    {
        return RawEdge( segOne.x1_, min(min(segOne.y1_, segTwo.y1_), min(segOne.y2_, segTwo.y2_))
                      , segOne.x1_, max(max(segOne.y1_, segTwo.y1_), max(segOne.y2_, segTwo.y2_)) );
    } 
    else if (segOne.InX() && segTwo.InX() && segOne.y1_ == segTwo.y1_) // overlap in x
    {
        return RawEdge( min(min(segOne.x1_, segTwo.x1_), min(segOne.x2_, segTwo.x2_)), segOne.y1_
                      , max(max(segOne.x1_, segTwo.x1_), max(segOne.x2_, segTwo.x2_)), segOne.y1_ );
    }
    else
    {
        throw ("No over lap while asked to merge?");
    }
}

void MergeReadSegments(std::list<RawEdge>& rawSegments, const std::vector <std::string> segments)
{
    using namespace std;
    list<RawEdge>::iterator itor;
    // read in edge segments raw data
    for (size_t i=0; i<segments.size(); ++i)
    {
        stringstream strStream(segments[i]);
        int x1, y1, x2, y2;
        strStream >> skipws >> x1;
        strStream >> skipws >> y1;
        strStream >> skipws >> x2;
        strStream >> skipws >> y2;

        RawEdge newEdge(x1, y1, x2, y2);

        // Merge overlaped raw edges
        itor=rawSegments.begin();
        while (rawSegments.empty()==false && itor!=rawSegments.end())
        {
            if (HasOverlap(newEdge, *itor))
            {
                newEdge = MergeOverlap(newEdge, *itor);
                itor = rawSegments.erase(itor);
            }
            else
            {
                ++itor;
            }
        }
        // Add new merged raw edge
        rawSegments.push_back(newEdge);
    }
}

void RawSegsToEdgesXY(std::list<RawEdge>& xEdges, std::list<RawEdge>& yEdges,
                      const std::list<RawEdge>& rawEdges)
{
    using namespace std;
    for (std::list<RawEdge>::const_iterator rawItor = rawEdges.begin(); rawItor!=rawEdges.end(); ++rawItor)
    {
        if ( (*rawItor).x1_ == (*rawItor).x2_ )
        {
            // added to xEdges
            if ( (*rawItor).y1_ < (*rawItor).y2_ )
            {
                yEdges.push_back( RawEdge((*rawItor).x1_, (*rawItor).y1_,
                    (*rawItor).x2_, (*rawItor).y2_) );
            } 
            else if ( (*rawItor).y2_ < (*rawItor).y1_ )
            {
                yEdges.push_back( RawEdge((*rawItor).x1_, (*rawItor).y2_,
                    (*rawItor).x2_, (*rawItor).y1_) );
            }
            else
            {
                // safe to discard?
            }
        } 
        else if ( (*rawItor).y1_ == (*rawItor).y2_ )
        {
            // added to yEdges
            if ( (*rawItor).x1_ < (*rawItor).x2_ )
            {
                xEdges.push_back( RawEdge((*rawItor).x1_, (*rawItor).y1_,
                    (*rawItor).x2_, (*rawItor).y2_) );
            } 
            else if ( (*rawItor).x2_ < (*rawItor).x1_ )
            {
                xEdges.push_back( RawEdge((*rawItor).x2_, (*rawItor).y1_,
                    (*rawItor).x1_, (*rawItor).y2_) );
            }
            else
            {
                // safe to discard?
            }
        }
        else
        {
            // input error
            throw("segment not level input error!");
        }
    }
}

void ProcessIntersectons( std::list<RawEdge>& xEdges, std::list<RawEdge>& yEdges)
{
    using namespace std;
    for (std::list<RawEdge>::iterator xItor=xEdges.begin(); xItor!=xEdges.end(); ++xItor)
    {
        std::list<RawEdge>::iterator yItor=yEdges.begin();
        while ( yItor!=yEdges.end() )
        {
            if (DoIntersectHardToSplitY(*xItor, *yItor) == true)
            {
                if ((*yItor).y1_ < (*xItor).y1_)
                {
                    yEdges.push_back( RawEdge((*yItor).x1_, (*yItor).y1_, (*yItor).x1_, (*xItor).y1_) );
                }

                if ((*xItor).y2_ < (*yItor).y2_)
                {
                    yEdges.push_back( RawEdge((*yItor).x2_, (*xItor).y2_, (*yItor).x2_, (*yItor).y2_) );
                }
                yItor = yEdges.erase(yItor);
            }
            else
            {
                ++yItor;
            }
        }
    }

    for (std::list<RawEdge>::iterator yItor=yEdges.begin(); yItor!=yEdges.end(); ++yItor)
    {
        std::list<RawEdge>::iterator xItor=xEdges.begin();
        while (xItor!=xEdges.end())
        {
            if (DoIntersectHardToSplitX(*xItor, *yItor) == true)
            {
                if ((*xItor).x1_ < (*yItor).x1_)
                {
                    xEdges.push_back( RawEdge((*xItor).x1_, (*xItor).y1_, (*yItor).x1_, (*xItor).y1_) );
                }

                if ((*yItor).x1_ < (*xItor).x2_)
                {
                    xEdges.push_back( RawEdge((*yItor).x1_, (*xItor).y1_, (*xItor).x2_, (*xItor).y2_) );
                }
                xItor = xEdges.erase(xItor);
            }
            else
            {
                ++xItor;
            }
        }
    }
}

// custom has function
struct hash_int_vec2
{
    size_t operator() (const IntVector2 &xIn) const
    {
        return std::hash<int>() (xIn.x_) ^ std::hash<int>() (xIn.y_);
    }
};

void RawSegmentToGraph(std::unordered_map<IntVector2, int, hash_int_vec2>& vertices, std::vector<RawEdge>& edges,
                       const std::list<RawEdge>& rawEdges)
{
    using namespace std;
    // In this particular situation with given constrains ...
    // segX.x1_ < segX.x2_ and segY.y1_ < segY.y2_
    std::list<RawEdge> xEdges; // edges parallel to x-axis
    std::list<RawEdge> yEdges; // edges parallel to y-axis

    RawSegsToEdgesXY(xEdges, yEdges, rawEdges);

    ProcessIntersectons(xEdges, yEdges);

    edges.resize(xEdges.size() + yEdges.size());
    unsigned int idx = 0;
    // loop through edges parallel to x-axis
    for (std::list<RawEdge>::const_iterator itor=xEdges.begin(); itor!=xEdges.end(); ++itor)
    {
        edges[idx++] = (*itor);
        IntVector2 v1((*itor).x1_, (*itor).y1_);
        vertices[v1] = 0;
        IntVector2 v2((*itor).x2_, (*itor).y2_);
        vertices[v2] = 0;
    }
    // loop through edges parallel to y-axis
    for (std::list<RawEdge>::const_iterator itor=yEdges.begin(); itor!=yEdges.end(); ++itor)
    {
        edges[idx++] = (*itor);
        IntVector2 v1((*itor).x1_, (*itor).y1_);
        vertices[v1] = 0;
        IntVector2 v2((*itor).x2_, (*itor).y2_);
        vertices[v2] = 0;
    }
}

void GenerateGraph( std::vector<Vertex> &allVertices, std::vector<Edge> &allEdges,
                    std::unordered_map<IntVector2, int, hash_int_vec2>& vertices, 
                    const std::vector<RawEdge>& edges)
{
    using namespace std;

    // add all vertices
    unsigned int idx = 0;
    for (std::unordered_map<IntVector2, int, hash_int_vec2>::iterator itov=vertices.begin(); itov!=vertices.end(); ++itov)
    {
        allVertices[idx] = Vertex( (*itov).first.x_, (*itov).first.y_);
        (*itov).second = idx;
        ++idx;
    }

    // recycle idx
    idx = 0;
    // add all edges
    for (std::vector<RawEdge>::const_iterator itoe=edges.begin(); itoe!=edges.end(); ++itoe)
    {
        IntVector2 v1((*itoe).x1_, (*itoe).y1_);
        Vertex* pv1 = &(allVertices[ vertices[v1] ]);
        IntVector2 v2((*itoe).x2_, (*itoe).y2_);
        Vertex* pv2 = &(allVertices[ vertices[v2] ]);
        allEdges[idx] = Edge(pv1, pv2);

        // Add nbor info to vertices back along with associated edges
        (pv1->nbors_).push_back(NborViaEdge(pv2));
        (pv2->nbors_).push_back(NborViaEdge(pv1));

        ++idx;
    }
}

// return number of components
int MarkByConnectedParts(std::vector<Vertex> &allVertices)
{
    using namespace std;

    int cid = 0;
    // Init vertices's cid to be zero (unprocessed)
    for (std::vector<Vertex>::iterator itor=allVertices.begin(); itor!=allVertices.end(); ++itor)
    {
        (*itor).cid_ = cid;
    }

    // BFS
    cid = 1;
    for (std::vector<Vertex>::iterator itor=allVertices.begin(); itor!=allVertices.end(); ++itor)
    {
        list<Vertex*> activeVertices;
        if ( (*itor).cid_ == 0 ) // never processed
        {
            activeVertices.push_back(&(*itor));
            while (activeVertices.empty() == false)
            {
                Vertex* currVex = activeVertices.front();
                for ( std::vector<NborViaEdge>::iterator iton = (currVex->nbors_).begin(); iton!=(currVex->nbors_).end(); ++iton )
                {
                    Vertex* nbr = (*iton).nbor_;
                    if (nbr->cid_ == 0) // never processed
                    {
                        activeVertices.push_back(nbr);
                    }
                }
                currVex->cid_ = cid;
                activeVertices.pop_front();
            }
            ++cid;
        }
    }

    return cid-1;
}

// custom has function
struct hash_int_vex
{
    size_t operator() (const Vertex &xIn) const
    {
        return std::hash<int>() (xIn.x_) ^ std::hash<int>() (xIn.y_);
    }
};

void GenerateConnectedGraphes( std::vector<ConnectedGraph> &connectedGraphs, 
                               std::vector<Vertex> &allVertices, int cnum)
{
    using namespace std;

    // resize according to number of connected components
    connectedGraphs.clear();
    connectedGraphs.resize(cnum); 

    typedef std::unordered_map<Vertex, size_t, hash_int_vex> VexHash;
    vector< VexHash > vexTable(cnum); // hash table to help bookkeeping utilities

    // Init vertices's cid to be zero (unprocessed)
    for (std::vector<Vertex>::iterator itor=allVertices.begin(); itor!=allVertices.end(); ++itor)
    {
        (connectedGraphs[(*itor).cid_-1]).vertices_.push_back(*itor);
    }

    // use hashing to help identify vetices
    for (size_t j=0; j<connectedGraphs.size(); ++j)
    {
        for (size_t i=0; i<(connectedGraphs[j]).vertices_.size(); ++i)
        {
            (vexTable[j])[ ((connectedGraphs[j]).vertices_)[i] ] = i;
        }

        // Fix nbors to within each component
        for (size_t i=0; i<(connectedGraphs[j]).vertices_.size(); ++i)
        {
            for (size_t k=0; k<(connectedGraphs[j]).vertices_[i].nbors_.size(); ++k)
            {
                size_t idx = (vexTable[j])[ *((connectedGraphs[j]).vertices_[i].nbors_[k].nbor_) ];
                (connectedGraphs[j]).vertices_[i].nbors_[k].nbor_ = &((connectedGraphs[j]).vertices_[idx]);
            }
        }
    }
}

class PenLift
{
public:
    static int numTimes(std::vector <std::string> segments, int n);

private:
};

// Constraints
// -	segments will contain between 1 and 50 elements, inclusive.
// -	Each element of segments will contain between 7 and 50 characters, inclusive.
// -	Each element of segments will be in the format "<X1>_<Y1>_<X2>_<Y2>" (quotes for clarity). The underscore character represents exactly one space. The string will have no leading or trailing spaces.
// -	<X1>, <Y1>, <X2>, and <Y2> will each be between -1000000 and 1000000, inclusive, with no unnecessary leading zeroes.
// -	Each element of segments will represent a horizontal or vertical line segment. No line segment will reduce to a point.
// -	n will be between 1 and 1000000, inclusive.
int PenLift::numTimes(std::vector <std::string> segments, int repeatNum)
{
    using namespace std;

    list<RawEdge> rawSegments;
    MergeReadSegments(rawSegments, segments);

    std::unordered_map<IntVector2, int, hash_int_vec2> rawVertices;
    std::vector<RawEdge> rawEdges;
    RawSegmentToGraph(rawVertices, rawEdges, rawSegments);
    rawSegments.clear();

    // using a random access container for vertices for BFS
    vector<Vertex> graphVertices(rawVertices.size());
    vector<Edge> graphEdges(rawEdges.size());
    GenerateGraph(graphVertices, graphEdges, rawVertices, rawEdges);
    rawVertices.clear();
    rawEdges.clear();

    // in this problem no extra info needed other than nbor info
    int comNum = MarkByConnectedParts(graphVertices);
    vector<ConnectedGraph> connectedComponents;
    GenerateConnectedGraphes(connectedComponents, graphVertices, comNum);
    graphVertices.clear();

    int numPenLift = 0;
    for (vector<ConnectedGraph>::iterator cgitor=connectedComponents.begin(); cgitor!=connectedComponents.end(); ++cgitor)
    {
        ++numPenLift;
        numPenLift += (repeatNum % 2 == 0) ? 0 : (*cgitor).GetPenLiftNum();
    }

    return numPenLift-1;
}

int main()
{
    using namespace std;

    string segmentsString[] = 
    {"-252927 -1000000 -252927 549481","628981 580961 -971965 580961",
    "159038 -171934 159038 -420875","159038 923907 159038 418077",
    "1000000 1000000 -909294 1000000","1000000 -420875 1000000 66849",
    "1000000 -171934 628981 -171934","411096 66849 411096 -420875",
    "-1000000 -420875 -396104 -420875","1000000 1000000 159038 1000000",
    "411096 66849 411096 521448","-971965 580961 -909294 580961",
    "159038 66849 159038 -1000000","-971965 1000000 725240 1000000",
    "-396104 -420875 -396104 -171934","-909294 521448 628981 521448",
    "-909294 1000000 -909294 -1000000","628981 1000000 -909294 1000000",
    "628981 418077 -396104 418077","-971965 -420875 159038 -420875",
    "1000000 -1000000 -396104 -1000000","-971965 66849 159038 66849",
    "-909294 418077 1000000 418077","-909294 418077 411096 418077",
    "725240 521448 725240 418077","-252927 -1000000 -1000000 -1000000",
    "411096 549481 -1000000 549481","628981 -171934 628981 923907",
    "-1000000 66849 -1000000 521448","-396104 66849 -396104 1000000",
    "628981 -1000000 628981 521448","-971965 521448 -396104 521448",
    "-1000000 418077 1000000 418077","-1000000 521448 -252927 521448",
    "725240 -420875 725240 -1000000","-1000000 549481 -1000000 -420875",
    "159038 521448 -396104 521448","-1000000 521448 -252927 521448",
    "628981 580961 628981 549481","628981 -1000000 628981 521448",
    "1000000 66849 1000000 -171934","-396104 66849 159038 66849",
    "1000000 66849 -396104 66849","628981 1000000 628981 521448",
    "-252927 923907 -252927 580961","1000000 549481 -971965 549481",
    "-909294 66849 628981 66849","-252927 418077 628981 418077",
    "159038 -171934 -909294 -171934","-252927 549481 159038 549481"};

    size_t segCount = sizeof(segmentsString) / sizeof(segmentsString[0]);

    vector <string> segments(segCount);
    for (size_t i=0; i<segCount; ++i)
    {
        segments[i] = segmentsString[i];
    }

    int numTraces = 1;

    int numLifts = PenLift::numTimes(segments, numTraces);

    return 0;
}