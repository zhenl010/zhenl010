#ifndef HEAPED_MEDIAN_WINDOW_H
#define HEAPED_MEDIAN_WINDOW_H

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

// fixed size for performance?
template <typename KeyType, unsigned int window_size>
class HeapMedianWindow
{
public:
    // size_type is assumed to be some integer type
    typedef int size_type;

private:
    struct Node
    {
        KeyType data;
        Node* parent;
        Node* child;
    };

    size_type size_;
    Node elements_[window_size];
};

//////////////////////////////////////////////////////////////////////////
}

#endif