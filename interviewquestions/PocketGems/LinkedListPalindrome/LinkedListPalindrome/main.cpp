#include <iostream>

struct Node {
    Node(int x): data(x), next(NULL) {}
    int data;
    Node* next;
};

Node* ReverseList(Node* head) {
    Node* newhead = NULL;
    while (head != NULL) {
        Node* next = head->next;
        head->next = newhead;
        newhead = head;
        head = next;
    }
    return newhead;
}

Node* FindMiddle(Node* head) {
    Node* pone = head;
    Node* ptwo = head;
    while (ptwo!=NULL && ptwo->next!=NULL) {
        pone = pone->next;
        ptwo = ptwo->next->next;
    }
    return pone;
}

void AppendList(Node** head, Node* list) {
    Node** node = head;
    while ((*node) != NULL) {
        node = &((*node)->next);
    }
    *node = list;
}

Node* CreateNode(int x) {
    Node* node = new Node(x);
    return node;
}

void RemoveNode(Node** node) {
    delete *node;
    *node = NULL;
}

void RemoveList(Node** list) {
    while (*list != NULL) {
        Node* next = (*list)->next;
        delete *list;
        *list = next;
    }
}

void CoutList(Node* head) {
    while (head != NULL) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

bool IsPalindrome(Node* head) {
    Node* mid = FindMiddle(head);
    Node* reversed = ReverseList(mid);

    Node* pone = head;
    Node* ptwo = reversed;
    while (pone!=NULL && ptwo!=NULL && pone->data==ptwo->data) {
        pone = pone->next;
        ptwo = ptwo->next;
    }
    bool is_palindrome = (ptwo == NULL); // ptwo always ahead of pone

    ReverseList(reversed);
    return is_palindrome;
}

// recursive version is deceptively bad.......
bool isPalindrome(Node **left,Node *right) {
    if(!right) return true;

    bool isPali =  isPalindrome(left,right->next) && ((*left)->data == right->data);
    *left = (*left)->next;
    return isPali;
}

int main(int argc, char** argv) {

    while (true) {

        for (int list_size=1; list_size<10; ++list_size) {
            std::cout << "List size: " << list_size << std::endl;
            Node* testlist = NULL;
            for (int i=0; i<list_size/2; ++i) {
                AppendList(&testlist, CreateNode(i));
            }
            for (int i=list_size/2; i<list_size; ++i) {
                AppendList(&testlist, CreateNode(list_size-i-1));
            }
            CoutList(testlist);
            CoutList(FindMiddle(testlist));

            // std::cout << "Is Palindrome???" << std::endl;
            // if (IsPalindrome(testlist) != isPalindrome(&testlist, testlist)) {
            //     std::cout << "CONTRADICTING RESULTS!!!!";
            // }
            
            if (IsPalindrome(testlist)) {
                std::cout << "YES!";
            } else {
                std::cout << "NO!";
            }
            std::cout << std::endl;

            testlist = ReverseList(testlist);
            CoutList(testlist);
            CoutList(FindMiddle(testlist));

            RemoveList(&testlist);
        }

    }

    return 0;
}