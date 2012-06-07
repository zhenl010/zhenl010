//////////////////////////////////////////////////////////////////////////
// Knuth’s Dancing Links Algorithm
//////////////////////////////////////////////////////////////////////////
#ifndef ACTIVE_MAKER_TEMPLATE_H_
#define ACTIVE_MAKER_TEMPLATE_H_

namespace augment_puzzle_helpers
{
////////////////////////////////////////////////////////////////

// forward declare the iterator
template<typename ActiveType, int MAX_ACTIVE_NUM = 9> class ActiveMarkerIterator;

template<typename ActiveType, int MAX_ACTIVE_NUM = 9>
class ActiveMarker {
public:
    typedef int IdType;
    ActiveMarker() : activenum_(0), head_(&recs_[0]) { MarkAll(); }
    IdType Add(ActiveType x);
    void Mark(IdType idx);
    void DisMark(IdType idx);
    void UnMark(IdType idx);
    void MarkAll();
    void UnMarkAll();
    int ActiveNum();
    ActiveType Next();
    ActiveType At(IdType idx);

    // Iterator:
    typedef ActiveMarkerIterator<ActiveType, MAX_ACTIVE_NUM> iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef ActiveType value_type;
    typedef ActiveType* pointer;
    typedef ActiveType& reference;
    friend class ActiveMarkerIterator<ActiveType, MAX_ACTIVE_NUM>;
    iterator begin() { return iterator(*this, head_->next); }
    iterator end() { return iterator(*this, head_); }

private:
    struct Node {
        ActiveType data;
        Node* prev;
        Node* next;
    };

    void UnMarkNode(Node*);

    Node recs_[MAX_ACTIVE_NUM+1];
    Node* head_;
    int activenum_;
};

template<typename ActiveType, int MAX_ACTIVE_NUM>
typename ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::IdType
ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::Add(ActiveType x) {
    ++activenum_;
    recs_[activenum_].data = x;
    Node* node = &recs_[activenum_];
    UnMarkNode(node);
    return activenum_;
}

// precondition assumes At(idx) is active
template<typename ActiveType, int MAX_ACTIVE_NUM>
inline void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::Mark(IdType idx) {
    Node* node = &recs_[idx];
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

// Precondition assumes At(idx) was just marked and no internal changes happened
// template<typename ActiveType, int MAX_ACTIVE_NUM>
// inline void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::DisMark(IdType idx) {
//     Node* node = &recs_[idx];
//     node->next->prev = node;
//     node->prev->next = node;
// }

// Notice this would work even if Mark(idx-1) and Mark(idx) happened
template<typename ActiveType, int MAX_ACTIVE_NUM>
inline void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::UnMark(IdType idx) {
    Node* node = &recs_[idx];
    UnMarkNode(node);
}

template<typename ActiveType, int MAX_ACTIVE_NUM>
void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::MarkAll() {
    head_->next = head_;
    head_->prev = head_;
}

template<typename ActiveType, int MAX_ACTIVE_NUM>
void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::UnMarkAll() {
    MarkAll();
    for (IdType i=1; i<=activenum_; ++i) {
        UnMark(i);
    }
}

template<typename ActiveType, int MAX_ACTIVE_NUM>
inline int ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::ActiveNum() { return activenum_; }
template<typename ActiveType, int MAX_ACTIVE_NUM>
inline ActiveType ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::Next() { return head_->next->data; }
template<typename ActiveType, int MAX_ACTIVE_NUM>
inline ActiveType ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::At(IdType idx) { return recs_[idx].data; }

template<typename ActiveType, int MAX_ACTIVE_NUM>
inline void ActiveMarker<ActiveType, MAX_ACTIVE_NUM>::UnMarkNode(Node* node) {
    node->next = head_->next;
    head_->next->prev = node;
    head_->next = node;
    node->prev = head_;
}

//////////////////////////////////////////////////////////////////////////
// Iterator template:
//////////////////////////////////////////////////////////////////////////
template<typename T, int MAX_ACTIVE_NUM>
class ActiveMarkerIterator
{
public:
    typedef ActiveMarker<T, MAX_ACTIVE_NUM> container;
    typedef ActiveMarkerIterator<T, MAX_ACTIVE_NUM> iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef typename ActiveMarker<T, MAX_ACTIVE_NUM>::Node* NodePtr;

    ActiveMarkerIterator(container& mycontainer, NodePtr node);
    const container& container_ref() const { return container_; }
    const NodePtr position() const { return curr_node_; }

    inline T& operator*();
    inline bool operator==(const iterator&) const;
    inline bool operator!=(const iterator&) const ;
    iterator& operator++(); // prefix
    iterator operator++(int); // postfix

private:
    ActiveMarker<T, MAX_ACTIVE_NUM>& container_;
    NodePtr curr_node_;
};

template<typename T, int MAX_ACTIVE_NUM>
ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::ActiveMarkerIterator(container& mycontainer, NodePtr node)
    : container_(mycontainer), curr_node_(node) {
}

template<typename T, int MAX_ACTIVE_NUM>
T& ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::operator*() {
    return curr_node_->data;
}

template<typename T, int MAX_ACTIVE_NUM>
inline bool ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::operator==(const ActiveMarkerIterator<T, MAX_ACTIVE_NUM>& rhs) const {
    return ( &(this->container_ref()) == &(rhs.container_ref()) && (this->position() == rhs.position()) );
}

template<typename T, int MAX_ACTIVE_NUM>
inline bool ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::operator!=(const ActiveMarkerIterator<T, MAX_ACTIVE_NUM>& rhs) const {
    return !(*this == rhs);
}

template<typename T, int MAX_ACTIVE_NUM>
typename ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::iterator& ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::operator++() { // prefix
    curr_node_ = curr_node_->next;
    return *this;
}

template<typename T, int MAX_ACTIVE_NUM>
typename ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::iterator ActiveMarkerIterator<T, MAX_ACTIVE_NUM>::operator++(int) { // postfix
    iterator ans = *this;
    ++(*this);
    return ans;
}

////////////////////////////////////////////////////////////////
}

#endif