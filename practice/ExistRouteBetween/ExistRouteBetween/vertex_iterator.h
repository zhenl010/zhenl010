#ifndef VERTEX_ITERATOR_H_
#define VERTEX_ITERATOR_H_

#include "directed_graph.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class DirectedGraph::VertexIterator
{
public:
    VertexIterator(DirectedGraph& graph, DirectedGraph::Vertex* vertex);

    DirectedGraph::UniqueId VertexId() { return vertex_->uniqueid; }
    void* &VoidPtr() { return vertex_->vert_state; }
    DirectedGraph::NborIterator outgoing_begin();
    DirectedGraph::NborIterator outgoing_end();

    DirectedGraph::Vertex* operator*() { return vertex_; }
    bool operator==(const VertexIterator& rhs) const { return &(graph_)==&(rhs.graph_) && vertex_==rhs.vertex_; }
    bool operator!=(const VertexIterator& rhs) const { return !(*this==rhs); }
    VertexIterator& operator++(); // prefix
    VertexIterator operator++(int); // postfix

private:
    DirectedGraph& graph_;
    DirectedGraph::Vertex* vertex_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif