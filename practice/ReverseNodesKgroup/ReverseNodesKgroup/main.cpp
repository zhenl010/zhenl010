//////////////////////////////////////////////////////////////////////////
// Reverse Nodes in k-Group
// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
// If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
// You may not alter the values in the nodes, only nodes itself may be changed.
// Only constant memory is allowed.
// For example,
// Given this linked list: 1->2->3->4->5
// For k = 2, you should return: 2->1->4->3->5
// For k = 3, you should return: 3->2->1->4->5
//////////////////////////////////////////////////////////////////////////
#include <iostream>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x=0) : val(x), next(NULL) {}
};

void PrintList(ListNode* h)
{
    using namespace std;

    while(h)
    {
        cout << h->val << ',';
        h = h->next;
    }

    cout << endl;
}

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head==NULL || k<=1) return head;        
        ListNode* node = head;
        ListNode* newhead = ReversePartK(node, k);
        while(node->next != NULL) {
            ListNode* tail = node;
            node = node->next;
            tail->next = ReversePartK(node, k);
        }
        return newhead;
    }

private:
    ListNode* ReversePartK(ListNode *head, int k) {
        ListNode* newhead = NULL;
        ListNode* tail = head; // remember tail
        int count = 0;
        while (head!=NULL && count++<k)
        {
            ListNode* next = head->next;
            head->next = newhead;
            newhead = head;
            head = next;
        }
        tail->next = head; // join the list

        return count<k ? ReversePartK(newhead, count) : newhead;
    }
};

int main(int argc, char** argv)
{
    const int ITEM_COUNT = 10;
    ListNode items[ITEM_COUNT];
    for (int i=0; i<ITEM_COUNT-1; ++i)
    {
        items[i].val = i;
        items[i].next = &items[i+1];
    }
    items[ITEM_COUNT-1] = ITEM_COUNT-1;

    PrintList(&items[0]);

    Solution solver;
    ListNode* list = solver.reverseKGroup(&items[0], 4);
    PrintList(list);

    return 0;
}