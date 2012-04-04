#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* CreateNode(int value)
{
    Node* newnode = new Node;
    newnode->data = value;
    return newnode;
}

Node* ArrayToBst(int array[], int lf_idx, int rt_idx)
{
    if (rt_idx < lf_idx)
    {
        return nullptr;
    }

    int ct_idx = lf_idx + (rt_idx-lf_idx) / 2;
    Node* root = CreateNode(array[ct_idx]);
    root->left = ArrayToBst(array, lf_idx, ct_idx-1);
    root->right = ArrayToBst(array, ct_idx+1, rt_idx);
    return root;
}

int main(int argc, char** argv)
{
    const int ARRAY_SIZE = 5;
    int array[ARRAY_SIZE];
    for (int i=0; i<ARRAY_SIZE; ++i)
    {
        array[i] = i;
    }

    Node* root = ArrayToBst(array, 0, ARRAY_SIZE-1);

    return 0;
}