#include <iostream>
#include <vector>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// （1）给一个unsigned int数组，size为n，数组的sum = a，计算一个k的值，将数组中
// 所有大于k的数改为k之后，数组的sum变为b。Ex,  [1,2,5,7,7,8] = a = 30, b = 26,
// 那么k = 6，因为[1,2,5,6,6,6] = 26。
// 要求时间复杂度是n*logn.
// (2)给一张L*W的纸，给一堆 l(i)* w(i)的模板，每个size的模板有各自的price p(i)
// ，求这张纸所能剪出的最大值。
int getCutHeight (vector<int>& nums, int a, int b) {
    // assert a = sum(nums)
    sort(nums.begin(), nums.end());
    vector<int> segs(nums.size());
    int last = 0;
    for(size_t i=0; i<nums.size(); ++i) {
        segs[i] = (nums[i] - last)*(nums.size()-i);
        last = nums[i];
    }

    int area = 0;
    int idx = 0;
    while (idx<segs.size() && area < b) { area += segs[idx++]; }

    if (idx==segs.size()) throw("ERROR INPUT");

    --idx;
    return nums[idx] - (area-b)/(nums.size()-idx+1);
}

class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int num = 0;
        ListNode *p = head;
        while (p!=NULL) {
            ++num;
            p=p->next;
        }
        return sortedListToBST(&head, 0, num-1);
    }

    TreeNode *sortedListToBST(ListNode **head, int l, int r) {
        if (r<l) return NULL;

        int mid = l + (r-l)/2;
        TreeNode* left = sortedListToBST(head, l, mid-1);
        TreeNode* root = new TreeNode((*head)->val);
        *head = (*head)->next;
        TreeNode* right = sortedListToBST(head, mid+1, r);
        root->left = left;
        root->right = right;
        return root;
    }

    /// @TODO: the following is not working properly ... @@
    TreeNode *sortedListToCompleteBinaryTree(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head==NULL) return NULL;
        TreeNode *root = NULL;
        int cnt = 0;
        while (head!=NULL) {
            TreeNode *p = new TreeNode(head->val);
            p->left = root;
            root = p;
            ++cnt;
            head = head->next;
        }

        TreeNode **p = &root;
        int fac = 2;
        while ((cnt-1)/fac > 0) {
            p = &root;
            for (int i=0; i<cnt/fac; ++i) {
                rightRotate(p);
                p = &((*p)->left);
            }
            fac *= 2;
        }

        return root;
    }

private:
    void rightRotate(TreeNode** p) {
        TreeNode *q = (*p)->left;
        (*p)->left = q->right;
        q->right = *p;
        *p = q;
    }
};

ListNode *newHead(ListNode* head, int x) {
    ListNode *p = new ListNode(x);
    p->next = head;
    return p;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
    int arry[] = {4,6,87,93,46,8}; // 244
    vector<int> nums(arry, arry+6);
    int k = getCutHeight(nums, 244, 164);

    Solution solver;

    ListNode *head = NULL;
    head = newHead(head, 8);
    head = newHead(head, 5);
    head = newHead(head, 3);
    // head = newHead(head, 3);
    // head = newHead(head, 2);
    // head = newHead(head, 1);
    // head = newHead(head, 0);

    TreeNode* root = solver.sortedListToBST(head);

    return 0;
}