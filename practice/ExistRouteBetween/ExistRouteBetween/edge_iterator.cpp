#include "edge_iterator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

DirectedGraph::EdgeIterator::EdgeIterator(DirectedGraph& graph, DirectedGraph::Edge* edge)
: graph_(graph), edge_(edge)
{
}

DirectedGraph::UniqueId DirectedGraph::EdgeIterator::FromVertexId()
{
    return edge_->from->uniqueid;
}

DirectedGraph::UniqueId DirectedGraph::EdgeIterator::DestVertexId()
{
    return edge_->dest->uniqueid;
}

DirectedGraph::EdgeIterator& DirectedGraph::EdgeIterator::operator++() // prefix
{
    edge_ = edge_->next_edge;
    return *this;
}

DirectedGraph::EdgeIterator DirectedGraph::EdgeIterator::operator++(int) // postfix
{
    DirectedGraph::EdgeIterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}