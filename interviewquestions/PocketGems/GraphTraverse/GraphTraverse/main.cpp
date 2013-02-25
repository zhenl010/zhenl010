#include <iostream>
#include <vector>
#include <unordered_set>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct Node {
    vector<Node*> neighbors;
};

void DfsVisit(Node* node, unordered_set<Node*>& visited) {
    if ( (node == NULL) || (visited.find(node) == visited.end()) ) return;

    // visit node here

    vector<Node*>& nbors = node->neighbors;
    for (size_t i=0; i<nbors.size(); ++i) {
        DfsVisit(nbors[i], visited);
    }
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    return 0;
}