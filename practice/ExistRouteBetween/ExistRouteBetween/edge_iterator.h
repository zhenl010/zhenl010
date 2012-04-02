#ifndef edge_ITERATOR_H_
#define edge_ITERATOR_H_

#include "directed_graph.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class DirectedGraph::EdgeIterator
{
public:
    EdgeIterator(DirectedGraph& graph, DirectedGraph::Edge* vertex);

    DirectedGraph::UniqueId FromVertexId();
    DirectedGraph::UniqueId DestVertexId();

    DirectedGraph::Edge* operator*() { return edge_; }
    bool operator==(const EdgeIterator& rhs) const { return &(graph_)==&(rhs.graph_) && edge_==rhs.edge_; }
    bool operator!=(const EdgeIterator& rhs) const { return !(*this==rhs); }
    EdgeIterator& operator++(); // prefix
    EdgeIterator operator++(int); // postfix

private:
    DirectedGraph& graph_;
    DirectedGraph::Edge* edge_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif