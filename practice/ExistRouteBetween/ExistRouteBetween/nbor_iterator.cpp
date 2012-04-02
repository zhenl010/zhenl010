#include "nbor_iterator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

DirectedGraph::NborIterator::NborIterator(DirectedGraph& graph, DirectedGraph::OutgoingEdgeContainer::iterator& nbor)
: graph_(graph), nbor_(nbor)
{
}

DirectedGraph::UniqueId DirectedGraph::NborIterator::NborId()
{
    return (*nbor_)->dest->uniqueid;
}

DirectedGraph::NborIterator& DirectedGraph::NborIterator::operator++() // prefix
{
    ++nbor_;
    return *this;
}

DirectedGraph::NborIterator DirectedGraph::NborIterator::operator++(int) // postfix
{
    DirectedGraph::NborIterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}