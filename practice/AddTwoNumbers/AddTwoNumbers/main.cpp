#include <cassert>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* CreateNode(int x)
{
    ListNode* node = new ListNode(x);
    return node;
}

void InsertAfter(ListNode* newnode, ListNode* node)
{
    assert(node!=nullptr);

    newnode->next = node->next;
    node->next = newnode;
}

void CoutList(ListNode* node)
{
    ListNode* curr = node;
    while (curr != nullptr)
    {
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
        if(l1==nullptr && l2==nullptr) return nullptr;
        if(l1==nullptr || l2==nullptr)
        {
            ListNode* origin = l1==nullptr ? l2 : l1;
            ListNode* head = new ListNode(origin->val);
            ListNode* curr = head;
            while(origin->next!=nullptr)
            {
                origin = origin->next;
                curr->next = new ListNode(origin->val);
                curr = curr->next;
            }
            return head;
        }
        
        int digit = (l1->val+l2->val)%10;
        int carry = (l1->val+l2->val)/10;
        ListNode* head = new ListNode(digit);
        ListNode* curr = head;
        ListNode* lone = l1->next;
        ListNode* ltwo = l2->next;
        while(lone!=nullptr && ltwo!=nullptr)
        {
            digit = (carry+lone->val+ltwo->val)%10;
            carry = (carry+lone->val+ltwo->val)/10;
            curr->next = new ListNode(digit);
            curr = curr->next;
            lone = lone->next;
            ltwo = ltwo->next;
        }
        
        ListNode* origin = lone==nullptr ? ltwo : lone;
        while(origin!=nullptr)
        {
            digit = (carry+origin->val)%10;
            carry = (carry+origin->val)/10;
            curr->next = new ListNode(digit);
            curr =  curr->next;
            origin = origin->next;
        }
        
        if(carry != 0)
        {
            curr->next = new ListNode(carry);
            curr = curr->next;
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