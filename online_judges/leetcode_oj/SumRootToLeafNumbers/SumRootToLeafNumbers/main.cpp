#include <iostream>

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return PathSum(root, 0);
    }

private:
    int PathSum(TreeNode* root, int sum) {
        if (root==NULL) return 0; // default
        sum = sum*10 + root->val;
        return (root->left==NULL && root->right==NULL) ? sum : PathSum(root->left,  sum) + PathSum(root->right, sum);
    }
};

int main() {
    return 0;
}