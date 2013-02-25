#include <iostream>
#include <unordered_set>

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

Node* KthToTail(Node* head, int k) {
    if (head==NULL || k<0) return NULL;

    Node* node = head;
    Node* runner = head;
    int distance = 0;
    while (runner->next!=NULL && distance<k) {
        runner = runner->next;
        ++distance;
    }
    if (distance < k) return NULL; // less than k nodes

    while (runner->next != NULL) {
        node = node->next;
        runner = runner->next;
    }

    return node;
}

void RemoveNext(Node* node) { // remove node's next
    if (node!=NULL && node->next!=NULL) {
        Node* next = node->next;
        node->next = next->next;
        delete next;
    }
}

void PrintLinkedList(Node* node) {
    while(node != NULL) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

void RemoveDuplicates(Node* head) {
    if (head == NULL) return;

    std::unordered_set<int> known_values;
    known_values.insert(head->data);

    Node* node = head;
    while (node->next != NULL) {
        if (known_values.find(node->next->data) != known_values.end()) {
            RemoveNext(node);
        } else {
            known_values.insert(node->next->data);
            node = node->next;
        }
    }
}

Node* FindMiddleNode(Node* head) {
    Node* p1 = head;
    Node* p2 = head;

    while (p2!=NULL && p2->next!=NULL) {
        p1 = p1->next;
        p2 = p2->next->next;
    }

    return p1;
}

//partition a linked list around a value x so that all nodes
// less than x come before all nodes greater than x.
void PartitionList(Node** head, int x) {
    if (*head == NULL) return;

    Node* tail = *head;
    Node* next = tail->next;
    while (next != NULL) {
        if (next->data < x) {
            tail->next = next->next;
            next->next = *head;
            *head = next;
        } else {
            tail = next;
        }
        next = tail->next;        
    }
}

int main(int argc, char** argv) {
    Node* list = NULL;

    int list_size = 20;
    for (int i=0; i<list_size; ++i) {
        InsertToSorted( &list, rand()%(list_size/2) );
    }

    PrintLinkedList(list);

    std::cout << std::endl;

    int k = 3;
    std::cout << k << "th to the end is: " << KthToTail(list, k)->data << std::endl;

    std::cout << std::endl;

    RemoveDuplicates(list); 
    PrintLinkedList(list);

    std::cout << "the middle element is: " << FindMiddleNode(list)->data << std::endl;

    PartitionList(&list, 5);
    PrintLinkedList(list);

    PartitionList(&list, 10);
    PrintLinkedList(list);

    return 0;
}