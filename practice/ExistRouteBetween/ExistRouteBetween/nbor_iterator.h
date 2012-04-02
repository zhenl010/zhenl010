#ifndef NBOR_ITERATOR_H_
#define NBOR_ITERATOR_H_

#include "directed_graph.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class DirectedGraph::NborIterator
{
public:
    NborIterator(DirectedGraph& graph, DirectedGraph::OutgoingEdgeContainer::iterator& vertex);

    DirectedGraph::UniqueId NborId();

    DirectedGraph::OutgoingEdgeContainer::iterator operator*() { return nbor_; }
    bool operator==(const NborIterator& rhs) const { return &(graph_)==&(rhs.graph_) && nbor_==rhs.nbor_; }
    bool operator!=(const NborIterator& rhs) const { return !(*this==rhs); }
    NborIterator& operator++(); // prefix
    NborIterator operator++(int); // postfix

private:
    DirectedGraph& graph_;
    DirectedGraph::OutgoingEdgeContainer::iterator nbor_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif