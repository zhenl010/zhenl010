#include "nbor_iterator.h"
#include "vertex_iterator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

DirectedGraph::NborIterator::NborIterator(DirectedGraph& graph, DirectedGraph::OutgoingEdgeContainer::iterator& nbor)
: graph_(graph), nbor_(nbor)
{
}

DirectedGraph::UniqueId DirectedGraph::NborIterator::VertexId()
{
    return (*nbor_)->dest->uniqueid;
}

DirectedGraph::VertexIterator DirectedGraph::NborIterator::VertexIterator()
{
    return DirectedGraph::VertexIterator(graph_, (*nbor_)->dest);
}

DirectedGraph::LengthType DirectedGraph::NborIterator::Distance()
{
    return (*nbor_)->length;
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