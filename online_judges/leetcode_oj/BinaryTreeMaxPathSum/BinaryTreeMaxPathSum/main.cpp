#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxPathSum(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        maxsum_ = root->val;
        maxPathSumFrom(root);
        return maxsum_;
    }

private:
    int maxPathSumFrom(TreeNode* root) {
        int sum = root->val;
        if (root->left!=NULL && root->right!=NULL) {
            int left_sum = maxPathSumFrom(root->left);
            int right_sum = maxPathSumFrom(root->right);
            sum = max(sum, sum+max(left_sum, right_sum));
            maxsum_ = max(maxsum_, sum);
            maxsum_ = max(maxsum_, root->val+left_sum+right_sum);
        } else {
            if (root->left!=NULL) sum = max(sum, sum+maxPathSumFrom(root->left));
            if (root->right!=NULL) sum = max(sum, sum+maxPathSumFrom(root->right));
            maxsum_ = max(maxsum_, sum);
        }
        return sum;
    }

    int maxsum_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {

    return 0;
}