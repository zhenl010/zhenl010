//////////////////////////////////////////////////////////////////////////
// Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater
// than or equal to x.
// You should preserve the original relative order of the nodes in each of the two partitions.
// For example,
// Given 1->4->3->2->5->2 and x = 3,
// return 1->2->2->4->3->5.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

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
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* small_head = NULL;
        ListNode* small_tail = small_head;
        ListNode* large_head = NULL;
        ListNode* large_tail = large_head;
        while(head!=NULL) {
            ListNode* next = head->next;
            head->next = NULL;
            if(head->val < x) {
                AppendNode(small_head, small_tail, head);
            } else {
                AppendNode(large_head, large_tail, head);
            }
            head = next;
        }

        // merge if needed
        if (small_head != NULL) {
            small_tail->next = large_head;
        } else {
            small_head = large_head;
        }

        return small_head;
    }

private:
    void AppendNode(ListNode* &head, ListNode* &tail, ListNode* node)
    {
        if (tail == NULL) { // empty list
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    return 0;
}