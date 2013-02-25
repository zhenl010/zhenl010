#include <iostream>
#include <cassert>

struct Node {
    Node(int x): data(x), left(NULL), right(NULL) {}
    int data;
    Node* left;
    Node* right;
};

void InsertToTree(Node** node, int x) {
    if(*node == NULL) *node = new Node(x);

    if(x < (*node)->data) {
        InsertToTree( &((*node)->left), x );
    } else if ((*node)->data < x) {
        InsertToTree( &((*node)->right), x );
    }
}

void RotateLeft(Node** node) {
    assert(*node && (*node)->right);
    Node* p = *node;
    Node* q = p->right;
    p->right = q->left;
    q->left = p;
    *node = q;
}

void RotateRight(Node** node) {
    assert(*node && (*node)->left);
    Node* q = *node;
    Node* p = q->left;
    q->left = p->right;
    p->right = q;
    *node = p;
}

int main(int argc, char** argv) {
    return 0;
}