#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
// #include <unordered_map>

using namespace std;

class PowerOutage
{
public:
    int estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength);
};

struct Node;
struct NborVieDust
{
    NborVieDust(Node* nbr, int leng) : nbor_(nbr), length_(leng) {}

    Node* nbor_; // nbor junction
    int length_; // duct length
};

struct Node
{
    Node(int id) : ID_(id) {}

    int ID_; // junction

    enum NODE_STAT
    {
        NEVER = 0,
        INQUEUE = 1,
        DONE =2
    };

    NODE_STAT cdat_; // associate data

    vector<NborVieDust> nbors_;
};

// DFS
void EstimateLengths(Node* curNode, vector<Node> &nodes, int &totalLeng)
{
    curNode->cdat_ = Node::DONE;

    int maxNborLeng = 0;
    for (size_t i=0; i<curNode->nbors_.size(); ++i)
    {
        Node* nbrNode = curNode->nbors_[i].nbor_;
        if (nbrNode->cdat_ == Node::NEVER) // never processed
        {
            EstimateLengths(nbrNode, nodes, totalLeng);

            if ( curNode->nbors_[i].length_ > maxNborLeng )
            {
                maxNborLeng = curNode->nbors_[i].length_;
            }

            totalLeng += 2 * (curNode->nbors_[i].length_);
        }
    }

    totalLeng -= maxNborLeng;
}

int PowerOutage::estimateTimeOut(vector <int> fromJunction, vector <int> toJunction, vector <int> ductLength)
{
    vector<Node> junctions;
    map<int, size_t> jids;

    size_t idx = 0;
    for (size_t i=0; i<fromJunction.size(); ++i)
    {
        if (jids.find(fromJunction[i]) == jids.end())
        {
            junctions.push_back(Node(fromJunction[i]));
            jids[fromJunction[i]]=idx++;
        }

        // from constraints they are all of the same size
        if (jids.find(toJunction[i]) == jids.end())
        {
            junctions.push_back(Node(toJunction[i]));
            jids[toJunction[i]]=idx++;
        }
    }

    // add nbor info.
    for (size_t i=0; i<fromJunction.size(); ++i)
    {
        size_t idxFrm = jids[fromJunction[i]];
        size_t idxTo = jids[toJunction[i]];
        int length = ductLength[i];

        junctions[idxFrm].nbors_.push_back( NborVieDust(&junctions[idxTo], length) );
        junctions[idxTo].nbors_.push_back( NborVieDust(&junctions[idxFrm], length) );
    }

    // clear jids
    jids.clear();

    // init associate data
    for (size_t i=0; i<junctions.size(); ++i)
    {
        junctions[i].cdat_ = Node::NEVER;
    }
    // search paths
    int pathLength = 0;
    list<Node*> activeNodes;
    EstimateLengths(&junctions[0], junctions, pathLength);

    return pathLength;
}

int main()
{
    int fjs[] =
    {0,1,0};
    int toJs[] = 
    {1,2,3};
    int ductLs[] =
    {10,10,10};

    vector <int> fromJunction(fjs, fjs+sizeof(fjs)/sizeof(int));
    vector <int> toJunction(toJs, toJs+sizeof(toJs)/sizeof(int));
    vector <int> ductLength(ductLs, ductLs+sizeof(ductLs)/sizeof(int));

    PowerOutage potage;
    int esTime = potage.estimateTimeOut(fromJunction, toJunction, ductLength);

    return 0;
}