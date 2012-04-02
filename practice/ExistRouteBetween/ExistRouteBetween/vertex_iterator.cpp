#include "vertex_iterator.h"
#include "directed_graph.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

DirectedGraph::VertexIterator::VertexIterator(DirectedGraph& graph, DirectedGraph::Vertex* vertex)
: graph_(graph), vertex_(vertex)
{
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