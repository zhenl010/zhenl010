#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace { // unnamed namespace
//////////////////////////////////////////////////////////////////////////

struct Node {
    std::vector<Node*> neighbors;
};

typedef std::unordered_map<Node*, Node*> Gmap;
typedef std::queue<Node*> Gqueue;

// DFS
Node* CloneGraph(Node* root, Gmap& gmap) {
    if (gmap.find(root) == gmap.end()) {
        Node* clone = new Node();
        gmap[root] = clone;

        for (size_t i=0; i<root->neighbors.size(); ++i) {
            clone->neighbors.push_back(CloneGraph(root->neighbors[i], gmap));
        }
    }

    return gmap[root];
}

// BFS
Node* CloneGraph(Node* root) {
    if(!root) return NULL;

    Gqueue node_queue;
    node_queue.push(root);
    Gmap gmap;

    while (!node_queue.empty()) {
        Node* node = node_queue.front();
        for (std::vector<Node*>::size_type i=0; i<node->neighbors.size(); ++i) {
            Node* nbor = node->neighbors[i];
            if (gmap.find(nbor) == gmap.end()) {
                // first time reach this node, create clone and add to map
                Node* nbor_clone = new Node();
                gmap[nbor] = nbor_clone;
                node_queue.push(nbor);
            }
            ((gmap[node])->neighbors).push_back(gmap[nbor]); // update neighbors
        }
    }

    return gmap[root];
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    return 0;
}