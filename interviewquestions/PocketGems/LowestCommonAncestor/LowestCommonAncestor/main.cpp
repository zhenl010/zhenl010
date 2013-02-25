#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Lowest Common ancestor for a BST
Node* LowestCommonAncestor(Node* root, int x, int y) {
    if (root == NULL) return NULL;

    if (std::max(x,y) < root->data) {
        return LowestCommonAncestor(root->left, x, y);
    } else if (root->data < std::min(x,y)) {
        return LowestCommonAncestor(root->right, x, y);
    }

    return root;
}

// Lowest Common ancestor for a Binary Tree
Node* LowestCommonAncestor(Node* root, Node* p, Node* q) {
    if (root == NULL) return NULL;
    if ((root == p) || (root == q)) return root;

    Node* left_ancestor = LowestCommonAncestor(root->left, p, q);
    Node* right_ancestor = LowestCommonAncestor(root->right, p, q);

    if (left_ancestor!=NULL && right_ancestor!=NULL) return root;

    return left_ancestor!=NULL ? left_ancestor : right_ancestor;
}

int main(int argc, char** argv) {

}