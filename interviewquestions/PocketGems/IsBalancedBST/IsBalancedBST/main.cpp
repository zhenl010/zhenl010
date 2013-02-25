#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;    
};

struct TreeInfo {
    bool isBalanced;
    int height;
};

TreeInfo GetTreeInfo(TreeNode* root) {
    TreeInfo tree_info = { true, 0 };
    if (root == NULL) return tree_info;

    TreeInfo left_substree_info = GetTreeInfo(root->left);
    TreeInfo right_substree_info = GetTreeInfo(root->right);

    tree_info.height = 1+std::max(left_substree_info.height, right_substree_info.height);
    tree_info.isBalanced = left_substree_info.isBalanced && right_substree_info.isBalanced
                         && abs(left_substree_info.height-right_substree_info.height)<=1;
}

bool IsBalancedBST(TreeNode* root) {
    return GetTreeInfo(root).isBalanced;
}

// function to find the depth of a BST
int Depth(TreeNode* root) {
    if (!root) return 0;

    int left_depth = 1 + Depth(root->left);
    int right_depth = 1 + Depth(root->right);
    return left_depth < right_depth ? right_depth : left_depth;
}

int main(int argc, char** argv) {
    return 0;
}