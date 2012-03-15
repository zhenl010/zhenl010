#include <iostream>
#include <vector>
#include <unordered_map>

struct Node
{
    int value;
    std::vector<Node*> neighbors;
};

Node* NewNode(int value)
{
    Node* node = new Node;
    node->value = value;
    node->neighbors.clear();

    return node;
}

Node* AddToClone(std::unordered_map<Node*, Node*>& known_nodes, Node* curr)
{
    if (curr == nullptr)
    {
        return nullptr;
    }

    Node* clone;
    if (known_nodes.find(curr) == known_nodes.end())
    {
        clone = NewNode(curr->value);
        known_nodes[curr] = clone;
    } 
    else
    {
        clone = known_nodes[curr];
    }

    clone->neighbors.resize(curr->neighbors.size());
    for (int i=0; i<(int)curr->neighbors.size(); ++i)
    {
        clone->neighbors[i] = AddToClone(known_nodes, curr->neighbors[i]);
    }

    return clone;
}

Node* CopyGraph(Node* root)
{
    // add code here
    using namespace std;
    unordered_map<Node*, Node*> known_nodes; // maps from original to clone

    return AddToClone(known_nodes, root);
}

int main()
{
    Node* root = NewNode(0);

    Node* clone_root = CopyGraph(root);

    return 0;
}