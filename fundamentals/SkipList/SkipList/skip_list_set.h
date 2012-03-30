#ifndef SKIP_LIST_SET_H_
#define SKIP_LIST_SET_H_

#include <cassert>
#include "rand_height_generator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// forward declare the iterator
template <typename C> class SkipListSetIterator;

template <typename T, int MAX_HEIGHT>
class SkipListSet
{
public:
    // A very specific skip list type with predefined parameters
    static const int SKIP_LIST_PINV = 4;

    SkipListSet();
    ~SkipListSet();

    // Iterator:
    typedef SkipListSet<T, MAX_HEIGHT>          container;
    typedef SkipListSetIterator<container>      iterator;
    typedef size_t                              size_type;
    typedef T                                   value_type;
    typedef ptrdiff_t                           difference_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
    friend class SkipListSetIterator<container>;
    iterator begin() { return iterator(*this, head_node_->next_nodes[0]); }
    iterator end() { return iterator(*this, nullptr); }

    void Insert(T);
    bool Remove(T);
    T* Find(T x) { Node* node=FindNodeByValue(x); return node==nullptr ? nullptr : &node->data; }

private:
    struct Node
    {
        T data;
        int height;
        Node** next_nodes;
    };

    SkipListSet(const SkipListSet&);
    SkipListSet& operator=(const SkipListSet&);

    int curr_height_;
    Node* head_node_;
    Node** node_fix_;

    // Helper functions
    Node* CreateNode(int height);
    void ReleaseContent(Node* node);
    Node* FindNodeByValue(T);
};

template <typename T, int MAX_HEIGHT>
SkipListSet<T, MAX_HEIGHT>::SkipListSet()
: curr_height_(0)
{
    head_node_ = CreateNode(MAX_HEIGHT);
    node_fix_ = new Node* [MAX_HEIGHT];
}

template <typename T, int MAX_HEIGHT>
SkipListSet<T, MAX_HEIGHT>::~SkipListSet()
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

template <typename T, int MAX_HEIGHT>
void SkipListSet<T, MAX_HEIGHT>::Insert(T value)
{
    int height = RandHeight<MAX_HEIGHT, SKIP_LIST_PINV>::Instance().RandomHeight();
    Node* new_node = CreateNode(height);
    new_node->data = value;

    Node* curr_node = head_node_;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (curr_node->next_nodes[idx]!=nullptr && (curr_node->next_nodes[idx]->data)<value)
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
}

template <typename T, int MAX_HEIGHT>
bool SkipListSet<T, MAX_HEIGHT>::Remove(T value)
{
    Node* prev_node = head_node_;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (prev_node->next_nodes[idx]!=nullptr && (prev_node->next_nodes[idx]->data)<value)
        {
            prev_node = prev_node->next_nodes[idx];
        }
        node_fix_[idx] = prev_node;
    }

    Node* curr_node = prev_node->next_nodes[0];
    if (curr_node==nullptr || curr_node->data!=value)
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
    return true;
}

template <typename T, int MAX_HEIGHT>
typename SkipListSet<T, MAX_HEIGHT>::Node* SkipListSet<T, MAX_HEIGHT>::CreateNode(int height)
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

template<typename T, int MAX_HEIGHT>
void SkipListSet<T, MAX_HEIGHT>::ReleaseContent(Node* node)
{
    delete [] node->next_nodes;
    delete node;
}

template <typename T, int MAX_HEIGHT>
typename SkipListSet<T, MAX_HEIGHT>::Node* SkipListSet<T, MAX_HEIGHT>::FindNodeByValue(T value)
{
    Node* curr_node = head_node_;
    for (int idx = curr_height_-1; idx >= 0; --idx)
    {
        while (curr_node->next_nodes[idx]!=nullptr && (curr_node->next_nodes[idx]->data)<value)
        {
            curr_node = curr_node->next_nodes[idx];
        }
    }

    curr_node = curr_node->next_nodes[0];
    if (curr_node!=nullptr && (curr_node->data)==value)
    {
        return curr_node;
    } 
    else
    {
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif