#include <iostream>
#include <string>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x=0): val(x), next(NULL) {}
};

ListNode* NewNode(int x) {
  return new ListNode(x);
}

void CoutList(ListNode* head) {
  while (head!=NULL) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

bool IsPalindrome(ListNode** head, ListNode* tail) {
  if (tail==NULL) return true;
  if (!IsPalindrome(head, tail->next) || (*head)->val!=tail->val) return false;
  *head = (*head)->next;
  return true;
}

ListNode* Reverse(ListNode* head) {
  ListNode* p = NULL;
  while (head != NULL) {
    ListNode* q = head->next;
    head->next = p;
    p = head;
    head = q;
  }
  return p;
}

bool IsPalindrom(ListNode* head) {
  ListNode* mid = head;
  ListNode* tail = head;
  while (tail!=NULL && tail->next!=NULL) {
    mid = mid->next;
    tail = tail->next->next;
  }

  tail = Reverse(mid);
  mid = tail;
  bool ispal = true;
  while (ispal && tail!=NULL) {
    if (head->val != tail->val) { ispal=false; }
    head = head->next;
    tail = tail->next;
  }
  mid = Reverse(mid);

  return ispal;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  while (true) {
    ListNode* head = NULL;
    for (int i=0; i<rand()%1000; ++i) {
      ListNode* node = NewNode(rand());
      node->next = head;
      head = node;
    }

    if (IsPalindrome(&head, head) != IsPalindrom(head)) {
      CoutList(head);
      cout << "ERROR!!!" << endl;
    }
  }

  return 0;
}