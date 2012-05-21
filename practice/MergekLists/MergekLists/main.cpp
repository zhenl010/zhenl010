#include <vector>
#include <map>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        multimap<int, ListNode*> buffer;
        for(int i=0; i<(int)lists.size(); ++i) {
            if(lists[i]!=NULL) {
                buffer.insert(pair<int, ListNode*>(lists[i]->val, lists[i]));
            }
        }

        ListNode* head = NULL;
        ListNode* tail = NULL;
        // INIT
        if(buffer.empty() != true) {
            ListNode* node = buffer.begin()->second;
            ListNode* next = node->next;
            node->next = NULL;
            tail = node;
            head = node;
            buffer.erase(buffer.begin());
            if(next!=NULL) { buffer.insert(pair<int, ListNode*>(next->val, next)); }
        }
        // fillin
        while(buffer.empty() != true) {
            ListNode* node = buffer.begin()->second;
            ListNode* next = node->next;
            node->next = NULL;
            tail->next = node;
            tail = node;
            buffer.erase(buffer.begin());
            if(next!=NULL) { buffer.insert(pair<int, ListNode*>(next->val, next)); }
        }
        return head;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(l1==NULL) return l2;
        if(l2==NULL) return l1;
        if(l2->val < l1->val) swap(l1, l2);
        ListNode* head = l1;
        ListNode* next = l1->next;
        ListNode* tail = l1;
        l1->next = NULL;
        if(next != NULL) {
            l1 = next;
            if(l2->val < l1->val) swap(l1, l2);
        } else {
            l1 = l2;
            l2 = NULL;
        }
        while(l2 != NULL) {
            ListNode* next = l1->next;
            tail->next = l1;
            l1->next = NULL;
            tail = l1;
            if(next != NULL) {
                l1 = next;
                if(l2->val < l1->val) swap(l1, l2);
            } else {
                l1 = l2;
                l2 = NULL;
            }
        }
        tail->next = l1;
        return head;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    return 0;
}