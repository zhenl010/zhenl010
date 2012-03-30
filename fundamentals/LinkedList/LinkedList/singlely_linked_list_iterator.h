#ifndef SINGLELY_LINKED_LIST_ITERATOR_H_
#define SINGLELY_LINKED_LIST_ITERATOR_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename T>
class SinglelyLinkedListIterator
{
public:
    typedef SinglelyLinkedList<T> container;
    typedef SinglelyLinkedListIterator<T> iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef typename SinglelyLinkedList<T>::Node* NodePtr;

    SinglelyLinkedListIterator(container& mycontainer, NodePtr node);
    const container& container_ref() const { return container_; }
    const NodePtr position() const { return curr_node_; }

    inline T& operator*();
    inline bool operator==(const iterator&) const;
    inline bool operator!=(const iterator&) const ;
    iterator& operator++(); // prefix
    iterator operator++(int); // postfix

private:
    SinglelyLinkedList<T>& container_;
    NodePtr curr_node_;
};

template <typename T>
SinglelyLinkedListIterator<T>::SinglelyLinkedListIterator(container& mycontainer, NodePtr node)
: container_(mycontainer), curr_node_(node)
{
}

template <typename T>
T& SinglelyLinkedListIterator<T>::operator*()
{
    return curr_node_->data;
}

template <typename T>
inline bool SinglelyLinkedListIterator<T>::operator==(const SinglelyLinkedListIterator<T>& rhs) const
{
    return ( &(this->container_ref()) == &(rhs.container_ref()) && (this->position() == rhs.position()) );
}

template <typename T>
inline bool SinglelyLinkedListIterator<T>::operator!=(const SinglelyLinkedListIterator<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
typename SinglelyLinkedListIterator<T>::iterator& SinglelyLinkedListIterator<T>::operator++() // prefix
{
    curr_node_ = curr_node_->next;
    return *this;
}

template <typename T>
typename SinglelyLinkedListIterator<T>::iterator SinglelyLinkedListIterator<T>::operator++(int) // postfix
{
    iterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}

#endif