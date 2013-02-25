#include <iostream>
#include <stack>

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
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
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
    if (node == NULL) return NULL;

    if (node->right != NULL) {
        Node* minnode = node->right;
        while (minnode->left != NULL) {
            minnode = minnode->left;
        }
        return minnode;
    } else {
        Node* curr = node;
        while (curr->parent!=NULL && curr->parent->right==curr) {
            curr = curr->parent;
        }
        return (curr->parent == NULL) ? NULL : curr->parent;
    }
}

using namespace std;

class BstIterator {
public:
    BstIterator(Node* node);

    Node* operator*();
    BstIterator& operator++();
    BstIterator& operator++(int);
private:
    stack<Node*> path_;
};

BstIterator::BstIterator(Node* node) {
    while (node != NULL) {
        path_.push(node);
        node = node->left;
    }
}

Node* BstIterator::operator*() {
    return path_.empty() ? NULL : path_.top();
}

BstIterator& BstIterator::operator++() {
    Node* node = path_.top();
    if (node->right != NULL) {
        Node* tmp = node->right;
        while(tmp != NULL) {
            path_.push(tmp);
            tmp = tmp->left;
        }
    } else {
        while (!path_.empty() && path_.top()->left!=node) {
            node = path_.top();
            path_.pop();
        }
    }
    return *this;
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

// for (int i=0; i<BST_NODE_NUM; ++i)
// {
//     Node* succ = SuccesserNode(nodes[i]);
// 
//     if (succ != NULL)
//     {
//         cout << nodes[i]->data << "  ----->>  " << succ->data << endl;
//     } 
//     else
//     {
//         cout << "END of the BST!" << endl;
//     }
// }

    for (int i=0; i<BST_NODE_NUM; ++i) {
        BstIterator itr(nodes[i]);

        while (*itr != NULL) {
            cout << (*itr)->data << "  ----->>  " << endl;
            ++itr;
        }
        cout << "<<=============  ----->>  " << endl;
    }

    return 0;
}