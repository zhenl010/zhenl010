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
public:
    //////////////////////////////////////////////////////////////////////////
    // Given a sorted linked list, delete all duplicates such that each element appear only once.
    // For example,
    // Given 1->1->2, return 1->2.
    // Given 1->1->2->3->3, return 1->2->3.
    //////////////////////////////////////////////////////////////////////////
    ListNode *deleteDuplicates(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(head==NULL || head->next==NULL) return head;
        
        ListNode* tail = head;
        ListNode* curr = head->next;
        tail->next = NULL;
        while(curr != NULL) {
            ListNode* next = curr->next;
            if(curr->val != tail->val) {
                curr->next = NULL;
                tail->next = curr;
                tail = curr;
            } else {
                delete curr;
            }
            curr = next;
        }
        return head;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    return 0;
}