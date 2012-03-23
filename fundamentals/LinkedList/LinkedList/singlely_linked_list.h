//////////////////////////////////////////////////////////////////////////
// Naive implementation of singlely linked list
// no allocator, no size indicator
// has a forward iterator: http://www.cplusplus.com/reference/std/iterator/ForwardIterator/
//////////////////////////////////////////////////////////////////////////
#ifndef SINGLELY_LINKED_LIST_H_
#define SINGLELY_LINKED_LIST_H_

#define USING_STD_UNORDERED_SET_

#include <cassert>

#ifdef USING_STD_UNORDERED_SET_
#include <unordered_set>
#endif

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// forward declare the iterator
template <typename T> class SinglelyLinkedListIterator;

template <typename T>
class SinglelyLinkedList
{
public:
    SinglelyLinkedList(); // default constructor
    ~SinglelyLinkedList(); // default destructor

    // Iterator:
    typedef SinglelyLinkedListIterator<T> iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    friend class SinglelyLinkedListIterator< T >;
    iterator begin() { return iterator(*this, head_); }
    iterator end() { return iterator(*this, nullptr); }
    iterator KthToBack(int k) { return iterator(*this, KthToTail(k)); }

    // Capacity:
    bool IsEmpty() const;

    // Element access:
    T& front(); // Returns a reference to the first element
    T& back(); // Returns a reference to the last element

    // Modifiers:
    void PushFront(const T& val);
    void PushBack(const T& val);
    void PopFront();
    void Clear(); // clear all elements of the list

    // Operations:
    void MakeUnique(); // Remove duplicate values utilizing brute force for O(N*N) time, O(1) space
#ifdef USING_STD_UNORDERED_SET_
    void MakeUniqueViaHashing(); // Remove duplicate values utilizing hashing for O(N) time O(N) space
#endif
    void Partition(const T&);
    void Sort();
    void Reverse();
    void Remove(const T&); // Remove elements with specific value

private:
    // disable copy and assign constructors
    SinglelyLinkedList(const SinglelyLinkedList<T>&);
    SinglelyLinkedList<T>& operator=(const SinglelyLinkedList<T>&);

    struct Node
    {
        T data;
        Node* next;
    };

    // Core Helper functions
    Node* NewNode(const T& val) const;
    void InitFromEmpty(const T& val);
    void ClearContent(Node* node); // deallocate
    void RemoveNext(Node* node); // remove node's next node from current list

    // Marginal Helper functions
    Node* KthToTail(int k);
    Node* IsolateNext(Node* node); // cut and reton node->next

    // linked list head and tail
    Node* head_;
    Node* tail_;
};

//////////////////////////////////////////////////////////////////////////
// public functions:
//////////////////////////////////////////////////////////////////////////

template <typename T>
SinglelyLinkedList<T>::SinglelyLinkedList()
: head_(nullptr), tail_(nullptr)
{
}

template <typename T>
SinglelyLinkedList<T>::~SinglelyLinkedList() // default destructor
{
    Clear();
}

template <typename T>
bool SinglelyLinkedList<T>::IsEmpty() const
{
    return head_ == nullptr;
}

template <typename T>
T& SinglelyLinkedList<T>::front() // Returns a reference to the first element
{
    assert(head_ != nullptr);
    return head_->data;
}

template <typename T>
T& SinglelyLinkedList<T>::back() // Returns a reference to the last element
{
    assert(tail_ != nullptr);
    return tail_->data;
}

template <typename T>
void SinglelyLinkedList<T>::PushFront(const T& val)
{
    if (IsEmpty())
    {
        InitFromEmpty(val);
    } 
    else
    {
        Node* node = NewNode(val);
        node->next = head_;
        head_ = node;
    }
}

template <typename T>
void SinglelyLinkedList<T>::PushBack(const T& val)
{
    if (IsEmpty())
    {
        InitFromEmpty(val);
    } 
    else
    {
        Node* node = NewNode(val);
        tail_->next = node;
        tail_ = node;
    }
}

template <typename T>
void SinglelyLinkedList<T>::PopFront()
{
    if (head_ != nullptr)
    {
        if (head_->next == nullptr)
        { // both head_ and tail_ point to the same node
            ClearContent(head_);
            head_ = nullptr;
            tail_ = nullptr;
        } 
        else
        {
            Node* node = head_;
            head_ = head_->next;
            ClearContent(node);
        }
    }
}

template <typename T>
void SinglelyLinkedList<T>::Clear() // clear all elements of the list
{
    while(IsEmpty() == false)
    {
        PopFront();
    }
}

// Remove duplicate values utilizing brute force for O(N*N) time, O(1) space
template <typename T>
void SinglelyLinkedList<T>::MakeUnique()
{
    Node* node=head_;
    while (node!=tail_)
    {
        Node* probe=node;
        while (probe != tail_)
        {
            if (node->data == probe->next->data)
            {
                RemoveNext(probe);
            }
            else
            {
                probe=probe->next;
            }
        }

        // tail_ might move after RemoveNext
        if (node!=tail_)
        {
            node=node->next;
        }
    }
}

#ifdef USING_STD_UNORDERED_SET_
// Remove duplicate values utilizing hashing for O(N) time O(N) space:
template <typename T>
void SinglelyLinkedList<T>::MakeUniqueViaHashing()
{
    std::unordered_set<T> known_keys;
    Node* probe = head_;
    known_keys.insert(probe->data);
    while (probe != tail_)
    {
        if (known_keys.find(probe->next->data) != known_keys.end())
        {
            RemoveNext(probe);
        } 
        else
        {
            probe = probe->next;
            known_keys.insert(probe->data);
        }
    }
}
#endif

// rather long implementation ...
template<typename T>
void SinglelyLinkedList<T>::Partition(const T& x)
{
    if (head_==nullptr || head_==tail_)
    {
        return; // nothing to do
    }

    if (head_->data<x != true)
    {
        Node* probe = head_;
        while ( (probe!=tail_) && ((probe->next->data<x)!=true) )
        {
            probe = probe->next;
        }

        if (probe == tail_) // all elements large than x
        {
            return;
        }

        // Make it head_
        Node* next_node = IsolateNext(probe);
        next_node->next = head_;
        head_ = next_node;
    }
    
    // move runner till the first large element
    Node* pivot = head_;
    Node* runner = head_;
    while (runner!=tail_ && runner->next->data < x)
    {
        Node* next_node = runner->next;
        pivot = next_node;
        runner = next_node;
    }

    // Go through the rest of the list
    while (runner!=tail_)
    {
        if (runner->next->data < x)
        {
            // swap
            Node* next_node = IsolateNext(runner);
            next_node->next = pivot->next;
            pivot->next = next_node;
            pivot = next_node;
        } 
        else
        {
            runner = runner->next;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// private functions:
//////////////////////////////////////////////////////////////////////////

template <typename T>
typename SinglelyLinkedList<T>::Node* SinglelyLinkedList<T>::NewNode(const T& val) const
{
    Node* node = new Node;
    node->data = val;
    node->next = nullptr;
    return node;
}

template <typename T>
void SinglelyLinkedList<T>::InitFromEmpty(const T& val)
{
    head_ = NewNode(val);
    tail_ = head_;
}

template <typename T>
void SinglelyLinkedList<T>::ClearContent(Node* node) // deallocate
{
    delete node;
}

template <typename T>
void SinglelyLinkedList<T>::RemoveNext(Node* node) // remove node's next
{
    if (node!=nullptr && node->next!=nullptr)
    {
        Node* next_node = node->next;
        node->next = next_node->next;
        if (tail_ == next_node)
        {
            tail_ = node;
        }
        ClearContent(next_node);
    }
}

template <typename T>
typename SinglelyLinkedList<T>::Node* SinglelyLinkedList<T>::KthToTail(int k)
{
    if (k<0 || IsEmpty())
    {
        return nullptr;
    }

    Node* node=head_;
    Node* runner = head_;
    int distance = 0;
    while (runner!=tail_ && distance<k)
    {
        runner = runner->next;
        ++distance;
    }
    if (distance < k)
    {
        return nullptr;
    }

    while (runner != tail_)
    {
        node = node->next;
        runner = runner->next;
    }

    return node;
}

template <typename T>
typename SinglelyLinkedList<T>::Node* SinglelyLinkedList<T>::IsolateNext(Node* node) // cut and reton node->next
{
    Node* next_node = node->next;
    if (next_node == tail_)
    {
        tail_ = node;
    }
    node->next = next_node->next;
    return next_node;
}

//////////////////////////////////////////////////////////////////////////
}

#endif