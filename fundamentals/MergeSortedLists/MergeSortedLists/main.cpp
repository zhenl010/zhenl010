#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct Node { int val; Node *next; Node(int x):val(x), next(NULL) {} };

Node* MergeSortedLists(Node *p, Node *q) {
  Node *head = NULL;
  Node **curr = &head;
  while (p!=NULL && q!=NULL) {
    if (p->val < q->val) {
      *curr = p;
      p = p->next;
    } else {
      *curr = q;
      q = q->next;
    }
    curr = &((*curr)->next);
  }
  // attach leftovers
  *curr = (p==NULL) ? q : p;

  return head;
}

Node* ReverseList(Node* head) {
  Node *newh = NULL;
  while (head!=NULL) {
    Node* next = head->next;
    head->next = newh;
    newh = head;
    head = next;
  }
  return newh;
}

void CoutList(Node* head) {
  while (head!=NULL) {
    cout << head->val << ", ";
    head = head->next;
  }
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int range_size = 8;
  int reset_num = 6;
  Node* list_one = new Node(range_size+rand()%range_size);
  while(0<list_one->val) {
    Node* new_node = new Node(list_one->val-rand()%reset_num);
    new_node->next = list_one;
    list_one = new_node;
  }
  CoutList(list_one);
  Node* list_two = new Node(range_size+rand()%range_size);
  while(0<list_two->val) {
    Node* new_node = new Node(list_two->val-rand()%reset_num);
    new_node->next = list_two;
    list_two = new_node;
  }
  CoutList(list_two);

  Node* merged = MergeSortedLists(list_one, list_two);
  CoutList(merged);
  Node* reversed = ReverseList(merged);
  CoutList(reversed);

  return 0;
}