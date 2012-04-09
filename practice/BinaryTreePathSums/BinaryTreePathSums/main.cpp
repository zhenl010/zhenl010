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

void ClearNodes(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    ClearNodes(root->left);
    root->left = nullptr;
    ClearNodes(root->right);
    root->right = nullptr;
    delete root;
}

void CoutPathOfSum(Node* node, std::list<Node*>& path, const DataType& target)
{
    if (node == nullptr)
    {
        return;
    }

    path.push_back(node);
    // Check all new pathes and if there's any valid output that path
    DataType sum = node->data - node->data; // zero of type auto
    for (std::list<Node*>::reverse_iterator itor=path.rbegin(); itor!=path.rend(); ++itor)
    {
        sum += (*itor)->data;
        if (sum == target)
        {
            for (std::list<Node*>::reverse_iterator fitr=itor; fitr!=path.rbegin(); --fitr)
            {
                std::cout << (*fitr)->data << " ====>> ";
            }
            std::cout << node->data << std::endl;
        }
    }

    // DFS
    CoutPathOfSum(node->left, path, target);
    CoutPathOfSum(node->right, path, target);

    path.pop_back();
}

void CoutAllPathOfSum(Node* root, const DataType& target)
{
    std::list<Node*> path;
    CoutPathOfSum(root, path, target);
}

int main(int argc, char** argv)
{
    using namespace std;

    const int TREE_NODE_NUM = 23;
    Node* nodes[TREE_NODE_NUM];
    for (int i=0; i<TREE_NODE_NUM; ++i)
    {
        nodes[i] = CreateNode(i+1);
    }
    for (int i=0; i<(TREE_NODE_NUM+1)/2; ++i)
    {
        int lf_idx = 2*i+1;
        if (lf_idx<TREE_NODE_NUM)
        {
            InsertToLeft(nodes[i], nodes[lf_idx]);
        }
        int rt_idx = 2*i+2;
        if (rt_idx<TREE_NODE_NUM)
        {
            InsertToRight(nodes[i], nodes[rt_idx]);
        }
    }
    Node* root = nodes[0];

    using namespace std;
    for (DataType tarsum=1; tarsum<TREE_NODE_NUM*2; ++tarsum)
    {
        std::cout << endl << "TARGET: " << tarsum << endl;
        cout << "////////////////////////////////////////////////////" << endl;
        CoutAllPathOfSum(root, tarsum);
    }

    ClearNodes(root);
    root = nullptr;

    return 0;
}