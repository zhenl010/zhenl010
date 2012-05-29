//////////////////////////////////////////////////////////////////////////
// Given a sorted linked list, delete all nodes that have duplicate numbers, 
// leaving only distinct numbers from the original list.
// For example,
// Given 1->2->3->3->4->4->5, return 1->2->5.
// Given 1->1->1->2->3, return 2->3.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    void PushBackList(ListNode* &head, ListNode* &tail, ListNode* node) {
        if (tail == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

public:
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* prev = head;
        ListNode* curr = prev==NULL ? NULL : prev->next;
        ListNode* tail = NULL;
        head = NULL;
        while(curr!=NULL) {
            ListNode* next = curr->next;
            if(curr->val != prev->val) {
                prev->next = NULL;
                PushBackList(head, tail, prev);
                prev = curr;
                curr = next;
            } else {
                while(next!=NULL && next->val==prev->val) {
                    ListNode* skip = next;
                    next = next->next;
                    delete skip;
                }
                prev = next;
                curr = prev==NULL ? NULL : prev->next;
            }
        }

        if (prev!=NULL) PushBackList(head, tail, prev);
        return head;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    return 0;
}