#include <iostream>

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

bool IdenticalCover(Node* root, Node* node)
{
    if (node == nullptr)
    {
        return true;
    }

    if (root == nullptr)
    {
        return false;
    }

    if ( (root->data)<(node->data) || (node->data)<(root->data) )
    {
        return false;
    }

    return IdenticalCover(root->left, node->left) && IdenticalCover(root->right, node->right);
}

bool IsSubtreeOfaBinaryTree(Node* root, Node* node)
{
    if (IdenticalCover(root, node))
    {
        return true;
    }

    if (root == nullptr)
    {
        return false;
    }

    return IsSubtreeOfaBinaryTree(root->left, node) || IsSubtreeOfaBinaryTree(root->right, node);
}

int main(int argc, char** argv)
{
    using namespace std;

    const int LARGE_TREE_NODE_NUM = 15;
    Node* large_tree_nodes[LARGE_TREE_NODE_NUM];
    for (int i=0; i<LARGE_TREE_NODE_NUM; ++i)
    {
        large_tree_nodes[i] = CreateNode(i+1);
    }
    for (int i=0; i<(LARGE_TREE_NODE_NUM+1)/2; ++i)
    {
        int lf_idx = 2*i+1;
        if (lf_idx<LARGE_TREE_NODE_NUM)
        {
            InsertToLeft(large_tree_nodes[i], large_tree_nodes[lf_idx]);
        }
        int rt_idx = 2*i+2;
        if (rt_idx<LARGE_TREE_NODE_NUM)
        {
            InsertToRight(large_tree_nodes[i], large_tree_nodes[rt_idx]);
        }
    }

    const int SMALL_TREE_NODE_NUM = 5;
    Node* small_tree_nodes[SMALL_TREE_NODE_NUM];
    for (int i=0; i<SMALL_TREE_NODE_NUM; ++i)
    {
        small_tree_nodes[i] = CreateNode(i+1);
    }
    for (int i=0; i<(SMALL_TREE_NODE_NUM+1)/2; ++i)
    {
        int lf_idx = 2*i+1;
        if (lf_idx<SMALL_TREE_NODE_NUM)
        {
            InsertToLeft(small_tree_nodes[i], small_tree_nodes[lf_idx]);
        }
        int rt_idx = 2*i+2;
        if (rt_idx<SMALL_TREE_NODE_NUM)
        {
            InsertToRight(small_tree_nodes[i], small_tree_nodes[rt_idx]);
        }
    }

    for (int i=0; i<LARGE_TREE_NODE_NUM; ++i)
    {
        for (int j=0; j<SMALL_TREE_NODE_NUM; ++j)
        {
            bool isSubtree = IsSubtreeOfaBinaryTree(large_tree_nodes[i], small_tree_nodes[j]);

            if (isSubtree == true)
            {
                cout << large_tree_nodes[i]->data << "  has a subtree identical to : " << small_tree_nodes[j]->data << endl;
            }
        }
    }

    return 0;
}