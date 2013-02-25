#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x): data(x), next(NULL) {}
};

Node* CreateNode(int x) {
    Node* node = new Node(x);
    return node;
}

void InsertAfter(Node* tail, int x) {
    Node* node = CreateNode(x);
    node->next = tail->next;
    tail->next = node;
}

Node* CloneLinkedList(Node* head) {
    if (!head) return NULL;

    Node* new_head = CreateNode(head->data);
    Node* new_tail = new_head;

    for (Node* node=head->next; node!=NULL; node=node->next) {
        InsertAfter(new_tail, node->data);
        new_tail = new_tail->next;
    }

    return new_head;
}

Node* ReverseLinkedList(Node* head) {
    if (!head) return head;

    Node* new_head = head;
    Node* node = head->next; // head will become the new tail
    while (node) {
        head->next = node->next;
        node->next = new_head;
        new_head = node;
        node = head->next;
    }

    return new_head;
}

void PrintLinkedList(Node* h) {
    while(h) {
        std::cout << h->data << " ";
        h = h->next;
    }
    std::cout << std::endl;
}

int main() {
    Node* list = CreateNode(0);
    InsertAfter(list, 1);
    InsertAfter(list, 2);
    InsertAfter(list, 3);
    InsertAfter(list, 4);

    PrintLinkedList(list);

    list = CreateNode(999);
    list = ReverseLinkedList(list);

    PrintLinkedList(list);

    return 0;
}