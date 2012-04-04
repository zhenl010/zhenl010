#include <iostream>
#include <list>

typedef int DataType;

struct Node
{
    DataType data;
    Node* left;
    Node* right;
};

Node* CreateNode(const DataType& value)
{
    Node* node = new Node;
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void InsertToLeft(Node* node, Node* newnode)
{
    newnode->left = node->left;
    node->left = newnode;
}

void InsertToRight(Node* node, Node* newnode)
{
    newnode->right = node->right;
    node->right = newnode;
}

void BinaryTreeByLevel(std::list< std::list<DataType> >& nodelayers, std::list<Node*>& layer)
{
    std::list<DataType> currlist;
    std::list<Node*> nextlayer;
    while (layer.empty() == false)
    {
        Node* node = layer.front();
        layer.pop_front();
        if (node!=nullptr)
        {
            currlist.push_back(node->data);
            nextlayer.push_back(node->left);
            nextlayer.push_back(node->right);
        }
    }

    if (currlist.empty()!=true)
    {
        nodelayers.push_back(currlist);
        BinaryTreeByLevel(nodelayers, nextlayer);
    }
}

void BinaryTreeByLevel(Node* node, std::list< std::list<DataType> >& nodelayers)
{
    if (node == nullptr)
    {
        return;
    }

    using namespace std;
    list<Node*> layer;
    layer.push_back(node);

    BinaryTreeByLevel(nodelayers, layer);
}

void BinaryTreeByLevelIter(Node* node, std::list< std::list<DataType> >& nodelayers)
{
    if (node == nullptr)
    {
        return;
    }

    using namespace std;
    list<Node*> layer;
    layer.push_back(node);
    std::list<DataType> currlist;
    do 
    {
        currlist.clear();
        std::list<Node*> nextlayer;
        while (layer.empty() == false)
        {
            Node* node = layer.front();
            layer.pop_front();
            if (node!=nullptr)
            {
                currlist.push_back(node->data);
                nextlayer.push_back(node->left);
                nextlayer.push_back(node->right);
            }
        }

        if (currlist.empty()!=true)
        {
            nodelayers.push_back(currlist);
            layer = nextlayer;
        }
    } while (currlist.empty() != true);
}

int main(int argc, char** argv)
{
    using namespace std;

    Node* root = CreateNode(20);
    Node* node_001 = CreateNode(10);
    Node* node_002 = CreateNode(30);
    Node* node_003 = CreateNode(25);
    InsertToLeft(root, node_001);
    InsertToRight(root, node_002);
    InsertToRight(node_001, node_003);

    //////////////////////////////////////////////////////////////////////////

    std::list< std::list<DataType> > nodelayers;
    BinaryTreeByLevel(root, nodelayers);

    std::list< std::list<DataType> > datalayers;
    BinaryTreeByLevelIter(root, datalayers);

    return 0;
}