#ifndef SKIP_LIST_SET_H_
#define SKIP_LIST_SET_H_

#include <cassert>
#include <iterator>
#include "rand_height_generator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// TEMPLATE STRUCT less
template<class ComparableType>
struct DefaultLess
{	// functor for operator<
    bool operator()(const ComparableType& leftsidevalue, const ComparableType& rightsidevalue) const
    {	// apply operator< to operands
        return (leftsidevalue < rightsidevalue);
    }
};

template < typename T, int MAX_HEIGHT, typename CompareFunc = DefaultLess<T> >
class SkipListSet
{
public:
    // A very specific skip list type with predefined parameters
    static const int SKIP_LIST_PINV = 4;

    SkipListSet();
    ~SkipListSet();

    // forward declare the iterator
    class SkipListSetIterator;

    // Iterator:
    typedef SkipListSet<T, MAX_HEIGHT, CompareFunc>         container;
    typedef SkipListSetIterator                             iterator;
    typedef size_t                                          size_type;
    typedef T                                               value_type;
    typedef ptrdiff_t                                       difference_type;
    typedef const T*                                        pointer;
    typedef const T&                                        reference;
    friend class SkipListSetIterator;
    iterator begin() { return iterator(*this, head_node_->next_nodes[0]); }
    iterator end() { return iterator(*this, nullptr); }

    int Size() { return size_; }
    void Insert(const T&);
    bool Remove(const T&);
    T* Find(const T& x) { Node* node=FindNodeByValue(x); return node==nullptr ? nullptr : &node->data; }

private:
    struct Node
    {
        T data;
        int height;
        Node** next_nodes;
    };

    SkipListSet(const SkipListSet&);
    SkipListSet& operator=(const SkipListSet&);

    int size_;
    int curr_height_;
    Node* head_node_;
    Node** node_fix_;

    // Helper functions
    void ClearContent();
    Node* CreateNode(int height);
    void ReleaseContent(Node* node);
    Node* FindNodeByValue(T);
};

template < typename T, int MAX_HEIGHT, typename CompareFunc >
SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSet()
: size_(0), curr_height_(0)
{
    head_node_ = CreateNode(MAX_HEIGHT);
    node_fix_ = new Node* [MAX_HEIGHT];
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
SkipListSet<T, MAX_HEIGHT, CompareFunc>::~SkipListSet()
{
    ClearContent();
}

template < typename T, int MAX_HEIGHT, typename CompareFunc>
void SkipListSet<T, MAX_HEIGHT, CompareFunc>::Insert(const T& value)
{
    int height = RandHeight<MAX_HEIGHT, SKIP_LIST_PINV>::Instance().RandomHeight();
    Node* new_node = CreateNode(height);
    new_node->data = value;

    Node* curr_node = head_node_;
    CompareFunc less_func;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (curr_node->next_nodes[idx]!=nullptr && less_func(curr_node->next_nodes[idx]->data, value) )
        {
            curr_node = curr_node->next_nodes[idx];
        }
        node_fix_[idx] = curr_node;
    }

    if (curr_node->next_nodes[0]!=nullptr && (curr_node->next_nodes[0]->data)==value)
    {
        // do nothing if already exist
        return;
    }

    while (curr_height_ < new_node->height)
    {
        node_fix_[curr_height_++] = head_node_;
    }

    for (int idx=0; idx<(new_node->height); ++idx)
    {
        new_node->next_nodes[idx] = node_fix_[idx]->next_nodes[idx];
        node_fix_[idx]->next_nodes[idx] = new_node;
    }

    ++size_;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
bool SkipListSet<T, MAX_HEIGHT, CompareFunc>::Remove(const T& value)
{
    Node* prev_node = head_node_;
    CompareFunc less_func;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (prev_node->next_nodes[idx]!=nullptr && less_func(prev_node->next_nodes[idx]->data, value))
        {
            prev_node = prev_node->next_nodes[idx];
        }
        node_fix_[idx] = prev_node;
    }

    Node* curr_node = prev_node->next_nodes[0];
    if (curr_node==nullptr || less_func(value, curr_node->data))
    {
        return false;
    }

    for (int idx=0; idx<curr_height_; ++idx)
    {
        if (node_fix_[idx]->next_nodes[idx]!=nullptr)
        {
            node_fix_[idx]->next_nodes[idx] = node_fix_[idx]->next_nodes[idx]->next_nodes[idx];
        }
    }

    while (0<curr_height_ && head_node_->next_nodes[curr_height_-1]==nullptr)
    {
        --curr_height_;
    }

    ReleaseContent(curr_node);
    --size_;
    return true;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
void SkipListSet<T, MAX_HEIGHT, CompareFunc>::ClearContent()
{
    Node* curr_node = head_node_->next_nodes[0];
    while (curr_node != nullptr)
    {
        Node* next_node = curr_node->next_nodes[0];
        ReleaseContent(curr_node);
        curr_node = next_node;
    }
    ReleaseContent(head_node_);
    delete [] node_fix_;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::Node* SkipListSet<T, MAX_HEIGHT, CompareFunc>::CreateNode(int height)
{
    assert(0<height && height<=MAX_HEIGHT);

    Node* new_node = new Node;
    new_node->next_nodes = new Node* [height];
    new_node->height = height;

    for (int i=0; i<height; ++i)
    {
        new_node->next_nodes[i] = nullptr;
    }

    return new_node;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
void SkipListSet<T, MAX_HEIGHT, CompareFunc>::ReleaseContent(Node* node)
{
    delete [] node->next_nodes;
    delete node;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::Node* SkipListSet<T, MAX_HEIGHT, CompareFunc>::FindNodeByValue(T value)
{
    CompareFunc less_func;
    Node* curr_node = head_node_;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (curr_node->next_nodes[idx]!=nullptr && less_func(curr_node->next_nodes[idx]->data,value))
        {
            curr_node = curr_node->next_nodes[idx];
        }
    }

    curr_node = curr_node->next_nodes[0];
    if (curr_node==nullptr || less_func(value, curr_node->data))
    {
        return nullptr;
    } 
    else
    {
        return curr_node;
    }
}

// Iterator class
template < typename T, int MAX_HEIGHT, typename CompareFunc >
class SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator
: public std::iterator<std::forward_iterator_tag,
    typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::value_type,
    typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::difference_type,
    typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::pointer,
    typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::reference>
{
public:
    typedef typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::Node* NodePtr;

    SkipListSetIterator(SkipListSet<T, MAX_HEIGHT, CompareFunc>&, NodePtr);

    reference operator*() const { return node_->data; }
    bool operator==(const SkipListSetIterator& rhs) const { return &(container_)==&(rhs.container_) && node_==rhs.node_; }
    bool operator!=(const SkipListSetIterator& rhs) const { return !(*this==rhs); }
    SkipListSetIterator& operator++(); // prefix
    SkipListSetIterator operator++(int); // postfix

private:
    SkipListSet<T, MAX_HEIGHT, CompareFunc>& container_;
    NodePtr node_;
};

template < typename T, int MAX_HEIGHT, typename CompareFunc >
SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator::SkipListSetIterator(SkipListSet<T, MAX_HEIGHT, CompareFunc>& c, NodePtr node)
: container_(c), node_(node)
{
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator&
SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator
::operator++() // prefix
{
    node_ = node_->next_nodes[0];
    return *this;
}

template < typename T, int MAX_HEIGHT, typename CompareFunc >
typename SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator
SkipListSet<T, MAX_HEIGHT, CompareFunc>::SkipListSetIterator
::operator++(int) // prefix
{
    SkipListSetIterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}

#endif