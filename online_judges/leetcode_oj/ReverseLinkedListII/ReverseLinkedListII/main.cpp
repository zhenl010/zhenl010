#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head==NULL || m==n) return head;

        ListNode** start = &head;
        for (int i=1; i<m; ++i) start = &((*start)->next);
        ListNode* end = (*start)->next;
        for (int j=0; j<(n-m); ++j) end = end->next;
        ListNode* middle = end;
        ListNode* curr = (*start);
        while (curr->next != end) {
            *start = curr->next;
            curr->next = middle;
            middle = curr;
            curr = *start;
        }
        curr->next = middle;

        return head;
    }
};

int main() {
    Solution solver;

    ListNode* head = &ListNode(-1);
    head->next = &ListNode(-3);

    ListNode* newhead = solver.reverseBetween(head, 1, 2);

    return 0;
}

