//////////////////////////////////////////////////////////////////////////
// Given a linked list, swap every two adjacent nodes and return its head.
// For example,
// Given 1->2->3->4, you should return the list as 2->1->4->3.
// Your algorithm should use only constant space. You may not modify the values in the list,
// only nodes itself can be changed.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x =0) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode** last = &head;
        while((*last)!=NULL && (*last)->next!=NULL) {
            ListNode* curr = *last;
            ListNode* next = curr->next;
            curr->next = next->next;
            next->next = curr;
            (*last) = next;
            last = &(curr->next);
        }
        return head;
    }
};

// leetcodes:
void ReverseList(ListNode ** head, ListNode* tail)
{
    ListNode * p = *head;
    ListNode * q = tail;
    ListNode * n;

    //make 'next' pointer of node point to previous node
    while( p != tail)
    {
        n = p->next;
        p->next = q;

        q = p;
        p = n;
    }

    //make head pointer to new start
    *head = q;
}

ListNode *SwapPairs(ListNode *head) 
{
    ListNode ** h = &head;
    ListNode * t = head;
    ListNode * n = head;

    while(1)
    {
        int count = 2;
        while(--count > 0 && t != NULL)
        {
            t = t->next;
        }

        if (t == NULL) break;

        //after reverse the list, the head node would be the last node,
        //and pointer to the next segment, we need to reserve this node 
        //to find next start point
        n = *h;

        ReverseList(h, t->next);

        //begin next reverse
        h = &n->next;
        t= n->next;
    }

    return head;    
}

void PrintList(ListNode* head)
{
    while (head!=NULL)
    {
        cout << head->val<< ", ";
        head = head ->next;
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    const int size = 4;
    ListNode nodes[size];
    for (int i = 0; i < size; ++i)
    {
        nodes[i] = i;
        nodes[i].next = (i ==(size -1)? NULL :&nodes[i+1]);
    }

    PrintList(nodes);
    ListNode* head =  SwapPairs(nodes);
    PrintList(head);
    head =  SwapPairs(head);
    PrintList(head);

    Solution solver;
    head = solver.swapPairs(head);
    PrintList(head);

    return 0;
}