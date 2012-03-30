//////////////////////////////////////////////////////////////////////////
// implementation of skip list set iterator class (included in skip_list_set.h)
//////////////////////////////////////////////////////////////////////////
#ifndef SKIP_LIST_SET_ITERATOR_H_
#define SKIP_LIST_SET_ITERATOR_H_

#include <iterator>

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename Container>
class SkipListSetIterator
: public std::iterator<std::forward_iterator_tag, typename Container::value_type,
typename Container::difference_type, typename Container::pointer, typename Container::reference>
{
public:
    typedef typename Container::Node* NodePtr;
    typedef typename Container::iterator iterator;

    SkipListSetIterator(Container&, NodePtr);

    reference operator*();
    bool operator==(const SkipListSetIterator<Container>& rhs) const;
    bool operator!=(const SkipListSetIterator<Container>& rhs) const;
    SkipListSetIterator<Container>& operator++(); // prefix
    SkipListSetIterator<Container> operator++(int); // postfix

private:
    Container& container_;
    NodePtr node_;
};

template <typename Container>
SkipListSetIterator<Container>::SkipListSetIterator(Container& c, NodePtr node)
: container_(c), node_(node)
{
}

template <typename T>
typename SkipListSetIterator<T>::reference SkipListSetIterator<T>::operator*()
{
    return node_->data;
}

template <typename T>
inline bool SkipListSetIterator<T>::operator==(const SkipListSetIterator<T>& rhs) const
{
    return container_==rhs.container_ && node_==rhs.node_;
}

template <typename T>
inline bool SkipListSetIterator<T>::operator!=(const SkipListSetIterator<T>& rhs) const
{
    return !(*this==rhs);
}

template <typename T>
typename SkipListSetIterator<T>& SkipListSetIterator<T>::operator++() // prefix
{
    node_ = node_->next_nodes[0];
    return *this;
}

template <typename T>
typename SkipListSetIterator<T> SkipListSetIterator<T>::operator++(int) // prefix
{
    iterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}

#endif