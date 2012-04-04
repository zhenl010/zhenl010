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

bool HasNodeCovered(Node* root, Node* node)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root == node)
    {
        return true;
    }

    return HasNodeCovered(root->left, node) || HasNodeCovered(root->right, node);
}

Node* FirstCommonAncester(Node* root, Node* one, Node* two)
{
    // if one of them is nullptr return the other
    if (one == nullptr)
    {
        return two;
    }
    if (two == nullptr)
    {
        return one;
    }

    if (!HasNodeCovered(root, one) || !HasNodeCovered(root, two))
    {
        return nullptr;
    }

    if (HasNodeCovered(root->left, one) && HasNodeCovered(root->left, two))
    {
        return FirstCommonAncester(root->left, one, two);
    }

    if (HasNodeCovered(root->right, one) && HasNodeCovered(root->right, two))
    {
        return FirstCommonAncester(root->right, one, two);
    }

    return root;
}

int main(int argc, char** argv)
{
    using namespace std;

    const int BTREE_NODE_NUM = 5;

    Node* nodes[BTREE_NODE_NUM];
    for (int i=0; i<BTREE_NODE_NUM; ++i)
    {
        nodes[i] = CreateNode(i+1);
    }

    for (int i=0; i<(BTREE_NODE_NUM+1)/2; ++i)
    {
        int lf_idx = 2*i+1;
        if (lf_idx<BTREE_NODE_NUM)
        {
            InsertToLeft(nodes[i], nodes[lf_idx]);
        }
        int rt_idx = 2*i+2;
        if (rt_idx<BTREE_NODE_NUM)
        {
            InsertToRight(nodes[i], nodes[rt_idx]);
        }
    }

    for (int i=0; i<BTREE_NODE_NUM; ++i)
    {
        for (int j=0; j<BTREE_NODE_NUM; ++j)
        {
            Node* ancester = FirstCommonAncester(nodes[0], nodes[i], nodes[j]);

            if (ancester != nullptr)
            {
                cout << "First common ancester of " << nodes[i]->data << " and " << nodes[j]->data;
                cout << "  is: " << ancester->data << endl;
            }
        }
    }

    return 0;
}