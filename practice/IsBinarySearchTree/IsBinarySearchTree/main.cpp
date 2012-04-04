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

void InsertToLeft(Node* root, Node* node)
{
    node->left = root->left;
    root->left = node;
}

void InsertToRight(Node* root, Node* node)
{
    node->right = root->right;
    root->right = node;
}

DataType MaxValueUnder(Node* node)
{
    DataType maxval = node->data;

    if (node->left != nullptr)
    {
        maxval = std::max(maxval, MaxValueUnder(node->left));
    }

    if (node->right != nullptr)
    {
        maxval = std::max(maxval, MaxValueUnder(node->right));
    }

    return maxval;
}

DataType MinValueUnder(Node* node)
{
    DataType minval = node->data;

    if (node->left != nullptr)
    {
        minval = std::min(minval, MinValueUnder(node->left));
    }

    if (node->right != nullptr)
    {
        minval = std::min(minval, MinValueUnder(node->right));
    }

    return minval;
}

bool IsBinarySearchTree(Node* node, DataType min, DataType max)
{
    if (node == nullptr)
    {
        return true;
    }

    if (node->data<min || max<node->data)
    {
        return false;
    }

    return IsBinarySearchTree(node->left, min, node->data) && IsBinarySearchTree(node->right, node->data, max);
}

// ranged compare method
bool IsBinarySearchTree(Node* node)
{
    if (node==nullptr)
    {
        return true;
    }

    DataType min_value = MinValueUnder(node);
    DataType max_value = MaxValueUnder(node);

    return IsBinarySearchTree(node, min_value, max_value);
}

void InOrderTraversal(Node* node, std::list<DataType>& datalist)
{
    if (node == nullptr)
    {
        return;
    }

    InOrderTraversal(node->left, datalist);
    datalist.push_back(node->data);
    InOrderTraversal(node->right, datalist);
}

// Traversal in-order method
bool IsBST(Node* node)
{
    if (node==nullptr)
    {
        return true;
    }

    std::list<DataType> datalist;
    InOrderTraversal(node, datalist);

    std::list<DataType>::iterator prev = datalist.begin();
    std::list<DataType>::iterator curr = ++datalist.begin();
    while (curr != datalist.end())
    {
        if ((*curr) < (*prev))
        {
            return false;
        }
        prev = curr;
        ++curr;
    }

    return true;
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

    bool isBinarySearchTree = IsBinarySearchTree(root);

    bool isBST = IsBST(root);

    if (isBinarySearchTree != isBST)
    {
        cout << "INCONSISTENT RESULTS!!!" << endl;
    }

    return 0;
}