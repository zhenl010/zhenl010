#include <iostream>

typedef int DataType;

struct Node
{
    DataType data;
    Node* parent;
    Node* left;
    Node* right;
};

Node* CreateNode(const DataType& value)
{
    Node* node = new Node;
    node->data = value;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void InsertToLeft(Node* curr, Node* newnode)
{
    newnode->parent = curr;
    newnode->left = curr->left;
    curr->left = newnode;
}

void InsertToRight(Node* curr, Node* newnode)
{
    newnode->parent = curr;
    newnode->right = curr->right;
    curr->right = newnode;
}

Node* SuccesserNode(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right != nullptr)
    {
        Node* minnode = node->right;
        while (minnode->left != nullptr)
        {
            minnode = minnode->left;
        }
        return minnode;
    } 
    else
    {
        Node* curr = node;
        while (curr->parent!=nullptr && curr->parent->right==curr)
        {
            curr = curr->parent;
        }

        if (curr->parent == nullptr)
        {
            return nullptr;
        } 
        else
        {
            return curr->parent;
        }
    }
}

int main(int argc, char** argv)
{
    using namespace std;
    
    const int BST_NODE_NUM = 4;
    Node* nodes[BST_NODE_NUM];

    for (int i=0; i<BST_NODE_NUM; ++i)
    {
        nodes[i] = CreateNode(i+1);
    }

    for (int i=0; i<(BST_NODE_NUM+1)/2; ++i)
    {
        int lf_idx = i*2+1;
        if (lf_idx < BST_NODE_NUM)
        {
            InsertToLeft(nodes[i], nodes[lf_idx]);
        }
        int rt_idx = i*2+2;
        if (rt_idx < BST_NODE_NUM)
        {
            InsertToRight(nodes[i], nodes[rt_idx]);
        }
    }

    Node* root = nodes[0];

    for (int i=0; i<BST_NODE_NUM; ++i)
    {
        Node* succ = SuccesserNode(nodes[i]);

        if (succ != nullptr)
        {
            cout << nodes[i]->data << "  ----->>  " << succ->data << endl;
        } 
        else
        {
            cout << "END of the BST!" << endl;
        }
    }

    return 0;
}