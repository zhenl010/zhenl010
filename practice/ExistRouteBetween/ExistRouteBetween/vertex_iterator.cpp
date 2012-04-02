#include "vertex_iterator.h"
#include "directed_graph.h"
#include "nbor_iterator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

DirectedGraph::VertexIterator::VertexIterator(DirectedGraph& graph, DirectedGraph::Vertex* vertex)
: graph_(graph), vertex_(vertex)
{
}

DirectedGraph::NborIterator DirectedGraph::VertexIterator::outgoing_begin()
{
    return DirectedGraph::NborIterator(graph_, (vertex_->outgoing_edges).begin());
}

DirectedGraph::NborIterator DirectedGraph::VertexIterator::outgoing_end()
{
    return DirectedGraph::NborIterator(graph_, (vertex_->outgoing_edges).end());
}

DirectedGraph::VertexIterator& DirectedGraph::VertexIterator::operator++() // prefix
{
    vertex_ = vertex_->next_verts[0];
    return *this;
}

DirectedGraph::VertexIterator DirectedGraph::VertexIterator::operator++(int) // postfix
{
    VertexIterator ans = *this;
    ++(*this);
    return ans;
}

//////////////////////////////////////////////////////////////////////////
}