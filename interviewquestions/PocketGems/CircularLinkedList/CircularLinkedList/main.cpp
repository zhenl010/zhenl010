#include <iostream>
#include <cassert>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

struct Node
{
    int x;
    Node* next;
};

Node* NewNode(int val)
{
    Node* node = new Node;
    node->x = val;
    node->next = NULL;
    return node;
}

void CleanNode(Node* node)
{
    delete node;
}

Node* IsolateAfter(Node* node)
{
    assert(node != NULL);
    Node* next = node->next;
    assert(next != NULL);
    node->next = next->next;
    next->next = NULL;
    return next;
}

void InsertAfter(Node* node, Node* iso_node)
{
    assert(node!=NULL && iso_node!=NULL);
    iso_node->next = node->next;
    node->next = iso_node;
}

//////////////////////////////////////////////////////////////////////////

void CoutCircularList(Node* head)
{
    using namespace std;

    if (head==NULL)
    {
        cout << " EMPTY LIST " << endl;
        return;
    }

    cout << head->x << "  ";
    for (Node* probe=head->next; probe!=head; probe=probe->next)
    {
        cout << probe->x << "  ";
    }
    cout << endl;
}

void CoutLinearList(Node* head)
{
    using namespace std;

    if (head==NULL)
    {
        cout << " EMPTY LIST " << endl;
        return;
    }

    for (Node* probe=head; probe!=NULL; probe=probe->next)
    {
        cout << probe->x << "  ";
    }
    cout << endl;
}

// find the node that links a linear list and a circular list
Node* FindLinkNode(Node* linear_head) {
    // notice the fast is ahead of slow from the beginning
    Node* fast = linear_head->next;
    Node* slow = linear_head;

    // move both runner nodes with different speed
    while (fast!=slow && fast->next!=NULL && fast->next->next!=NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast!=slow) {
        return NULL; // no circle
    } else {
        // circle found now try to find the intersection
        Node* runner = linear_head;
        slow = slow->next;
        while (runner!=slow) {
            slow = slow->next;
            runner = runner->next;
        }
        return runner;
    }
}

const int CIRCULAR_LIST_SIZE = 6;
const int LINEAR_LIST_SIZE = 2;

//////////////////////////////////////////////////////////////////////////
}

int main()
{
    using namespace std;

    // create a circular link list with head:
    // Node* circular_head = NewNode(0);
    // circular_head->next = circular_head;
    // insert some elements
    // for (int i=0; i<CIRCULAR_LIST_SIZE; ++i)
    // {
    //     Node* cnode = NewNode(rand() % CIRCULAR_LIST_SIZE);
    //     InsertAfter(circular_head, cnode);
    // }
    // 
    // output circular list
    // CoutCircularList(circular_head);
    // 
    // create another link list without circle
    // Node* linear_head = NewNode(-1);
    // Node* linear_last = linear_head;
    // insert some elements
    // for (int i=0; i<LINEAR_LIST_SIZE; ++i)
    // {
    //     // insert some negative numbers
    //     Node* lnode = NewNode(rand() % LINEAR_LIST_SIZE - LINEAR_LIST_SIZE);
    //     InsertAfter(linear_last, lnode);
    //     linear_last = lnode;
    // }
    // 
    // output linear list
    // CoutLinearList(linear_head);
    // 
    // link linear list to circular list at a random node
    // Node* link_node = circular_head;
    // for (int i=0; i<(rand() % CIRCULAR_LIST_SIZE); ++i)
    // {
    //     link_node = link_node->next;
    // }
    // linear_last->next = link_node;
    // 
    // Node* cross_node = FindLinkNode(linear_head);
    // 
    // test whether the result is correct
    // assert(link_node == cross_node);
    // 
    // output circular part starting from the intersection
    // CoutCircularList(cross_node);

    return 0;
}