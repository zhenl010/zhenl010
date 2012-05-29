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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* rtn = head;
        while(n-->0) { rtn = rtn->next; }

        ListNode** skip = &head;
        while(rtn != NULL) {
            rtn = rtn->next;
            skip = &((*skip)->next);
        }
        ListNode* remove = *skip;
        *skip = (*skip)->next;
        delete remove;

        return head;
    }

    ListNode *RemoveNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* prt = head;
        for(int i=0; i<n; ++i) prt = prt->next;
        
        ListNode* skip = head;
        if(prt == NULL) {
            head = head->next;
        } else {
            ListNode* plf = head;
            prt = prt->next;        
            while(prt != NULL) {
                plf = plf->next;
                prt = prt->next;
            }
            skip = plf->next;
            plf->next = skip->next;
        }
        
        delete skip;
        return head;
    }
};

int main(int argc, char** argv)
{
    return 0;
}