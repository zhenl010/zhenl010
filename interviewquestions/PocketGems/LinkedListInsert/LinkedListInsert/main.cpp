#include <iostream>

struct Node {
    Node(int x): data(x), next(NULL) {}
    int data;
    Node* next;
};

// Insert to linked list
void InsertAt(Node** node, int x) {
    if ((*node) == NULL) { // empty node
        (*node) = new Node(x);
    } else {
        Node* new_node = new Node(x);
        new_node->next = *node;
        *node = new_node;
    }
}

// Insert a node to a SORTED link list.
void InsertToSorted(Node** node, int x) {
    while ( ((*node)!=NULL) && (((*node)->data) < x) ) {
        node = &((*node)->next);
    }

    InsertAt(node, x);
}

void PrintLinkedList(Node* node) {
    while(node != NULL) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    Node* list = NULL;

    for (int i=0; i<200; ++i) {
        InsertToSorted(&list, rand()%100);
    }

    PrintLinkedList(list);

    return 0;
}