#include <cassert>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* CreateNode(int x) {
    ListNode* node = new ListNode(x);
    return node;
}

void InsertAt(ListNode** node, int x) {
    *node = new ListNode(x);
}

void InsertAfter(ListNode* newnode, ListNode* node) {
    assert(node!=NULL);
    newnode->next = node->next;
    node->next = newnode;
}

void CoutList(ListNode* node) {
    ListNode* curr = node;
    while (curr != NULL) {
        std::cout << curr->val << "   ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(l1==NULL && l2==NULL) return NULL;

        int digit = 0;
        int carry = 0;
        ListNode* head = NULL;
        ListNode** curr = &head;
        while(l1!=NULL && l2!=NULL) {
            digit = (carry+l1->val+l2->val)%10;
            carry = (carry+l1->val+l2->val)/10;
            *curr = new ListNode(digit);
            curr = &((*curr)->next);
            l1 = l1->next;
            l2 = l2->next;
        }

        ListNode* origin = l1==NULL ? l2 : l1;
        while(origin!=NULL) {
            digit = (carry+origin->val)%10;
            carry = (carry+origin->val)/10;
            *curr = new ListNode(digit);
            curr = &((*curr)->next);
            origin = origin->next;
        }

        if(carry != 0) {
            *curr = new ListNode(carry);
        }

        return head;
    }
};

int main()
{
    ListNode* listone = CreateNode(2);
    InsertAfter(CreateNode(3), listone);
    InsertAfter(CreateNode(4), listone);
    CoutList(listone);

    ListNode* listtwo = CreateNode(5);
    InsertAfter(CreateNode(4), listtwo);
    InsertAfter(CreateNode(6), listtwo);
    CoutList(listtwo);

    Solution solver;
    ListNode* result = solver.addTwoNumbers(listone, listtwo);
    CoutList(result);

    return 0;
}