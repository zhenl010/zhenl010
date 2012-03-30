//////////////////////////////////////////////////////////////////////////
// Basic implementation of directed graph allowing vertex and edge changes
// inspired by: http://www.cs.bu.edu/teaching/c/graph/linked/
// each vertex has a unique id and a wraper might use map(id, info.) to manage
//////////////////////////////////////////////////////////////////////////
#ifndef BASIC_GRAPH_H_H
#define BASIC_GRAPH_H_H

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class DirectedGraph
{
public:
    typedef unsigned int UniqueId;
    typedef int LengthType;

    DirectedGraph();
    ~DirectedGraph();

    UniqueId NewVertex(); // returns the new vertex's id
    bool RemoveVertex(UniqueId); // fail when the id does not exist
    void AddEdge(UniqueId, UniqueId, LengthType);

    // allow access via iterator classes
    friend class VertexIterator;
    VertexIterator vert_begin();
    VertexIterator vert_end();
    friend class EdgeIterator;
    EdgeIterator edge_begin();
    EdgeIterator edge_end();

private:
    // disable copy and assign operations
    DirectedGraph(const DirectedGraph&);
    DirectedGraph& operator=(const DirectedGraph&);

    struct Vertex;
    struct Edge
    {
        Vertex* from;
        Vertex* dest;
        LengthType length;
        void* edge_state; // used to mark the edge to different states
        /// doubly-linked list for edges
        Edge* prev_edge;
        Edge* next_edge;
    };

    struct EdgeRef
    {
        Edge* edge;
        EdgeRef** next_edges;
    };

    struct Vertex
    {
        UniqueId uniqueid; // identity used to communicate with the world
        EdgeRef* edgeref_head; // edges starting from this vertex
        void* vert_state; // used to mark the vertex to different states
        /// listed implementation
        int height;
        Vertex** next_verts;
    };


    // vertex helper functions:
    UniqueId NextId() { return nextid_++; } // generate id within current graph
    Vertex* CreateVertex(int);
    void ReleaseContent(Vertex*);
    void InsertVetexOrDie(Vertex*);
    Vertex* FindById(UniqueId);

    // edge helper functions:
    Edge* CreateEdge(Vertex*, Vertex*, LengthType);
    void ReleaseContent(Edge*);
    void PushFrontGraphEdges(Edge*);
    void PushEdgerefToVertexFrom(Edge*);

    // private data:
    UniqueId nextid_;
    int curr_height_;
    Edge* edge_head_;
    Vertex* vert_head_; // sentinel
    Vertex** vert_fix_; // update finger
    EdgeRef** nbor_fix_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif