#include <iostream>
#include <vector>
#include <stack>

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
    vector<int> inorderTraversal(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> recs;
        TreeNode *p = root;
        TreeNode *anc = NULL;
        while (p != NULL) {
            anc = p->left;
            if(anc == NULL) { recs.push_back(p->val); p=p->right; continue; }
            
            while (anc->right!=NULL && anc->right!=p) anc = anc->right;
            if (anc->right == NULL) {
                anc->right = p; // mutation
                p = p->left;
            } else {
                recs.push_back(p->val);
                p=p->right;
                anc->right = NULL; // reset
            }
        }
        return recs;
    }

    vector<int> inorderTraversalFaster(TreeNode *root) { // used extra space though
        vector<int> result;
        if(root == NULL) return result;

        stack<TreeNode *> stk;
        stk.push(root);
        TreeNode *p = root->left;
        while(!stk.empty()) {
            while(p != NULL) {
                stk.push(p);
                p = p->left;
            }
            p = stk.top();
            stk.pop();
            result.push_back(p->val);

            p = p->right;
            if(p != NULL) {
                stk.push(p);
                p = p->left;
            }
        }

        return result;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    TreeNode* root = NULL;

    vector<int> recs = solver.inorderTraversalFaster(root);

    return 0;
}