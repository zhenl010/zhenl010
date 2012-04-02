#include "directed_graph.h"
#include <cassert>
#include <limits>
#include "skip_list_set.h"
#include "vertex_iterator.h"
#include "edge_iterator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const int VERTEX_LIST_HEIGHT = 10;
const int VERTEX_LIST_PINV = 4;

//////////////////////////////////////////////////////////////////////////
}

DirectedGraph::DirectedGraph()
: nextid_(0), curr_height_(0), edge_head_(nullptr)
{
    vert_head_ = CreateVertex(VERTEX_LIST_HEIGHT);
    vert_fix_ = new Vertex*[VERTEX_LIST_HEIGHT];
}

DirectedGraph::~DirectedGraph()
{
    Vertex* currvert=vert_head_->next_verts[0];
    while ( currvert != nullptr )
    {
        Vertex* nextvert = currvert->next_verts[0];
        ReleaseContent(currvert);
        currvert = nextvert;
    }
    ReleaseContent(vert_head_);
    delete [] vert_fix_;

    Edge* curredge =  edge_head_;
    while (curredge != nullptr)
    {
        Edge* nextedge = curredge->next_edge;
        ReleaseContent(curredge);
        curredge = nextedge;
    }
}

DirectedGraph::UniqueId DirectedGraph::NewVertex() // returns the new vertex's id
{
    int height = RandHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::Instance().RandomHeight();
    Vertex* new_vertex = CreateVertex(height);
    InsertVetexOrDie(new_vertex);

    return new_vertex->uniqueid;
}

bool DirectedGraph::AddEdge(UniqueId fromid, UniqueId destid, LengthType length)
{
    Vertex* vert_from = FindById(fromid);
    Vertex* vert_dest = FindById(destid);
    if (vert_from==nullptr || vert_dest==nullptr)
    {
        return false;
    }

    Edge* new_edge = CreateEdge(vert_from, vert_dest, length);
    // add new edge to graph edge list
    PushFrontEdge(new_edge);
    // add pointers the edge's end vertices's nbor-list
    vert_from->outgoing_edges.Insert(new_edge);
    vert_dest->incoming_edges.Insert(new_edge);
    return true;
}

bool DirectedGraph::RemoveVertex(UniqueId vid)
{
    using namespace augment_data_structure;

    Vertex* prev_vert = vert_head_;
    for (int idx = curr_height_-1; idx>=0; --idx)
    {
        while (prev_vert->next_verts[idx]!=nullptr && (prev_vert->next_verts[idx]->uniqueid)<vid)
        {
            prev_vert = prev_vert->next_verts[idx];
        }
        vert_fix_[idx] = prev_vert;
    }

    Vertex* curr_vert = prev_vert->next_verts[0];
    if ( curr_vert == nullptr || vid < curr_vert->uniqueid )
    {
        return false;
    }

    for (int idx=0; idx<curr_height_; ++idx)
    {
        if (vert_fix_[idx]->next_verts[idx] != nullptr)
        {
            vert_fix_[idx]->next_verts[idx] = vert_fix_[idx]->next_verts[idx]->next_verts[idx];
        }
    }       

    while ( 0<curr_height_ && vert_head_->next_verts[curr_height_-1]==nullptr )
    {
        --curr_height_;
    }

    for (IncomingEdgeContainer::iterator itor = (curr_vert->incoming_edges).begin();
        itor != (curr_vert->incoming_edges).end(); ++itor)
    {
        (*itor)->from->outgoing_edges.Remove(*itor);
        RemoveEdge(*itor);
    }

    for (OutgoingEdgeContainer::iterator itor = (curr_vert->outgoing_edges).begin();
        itor != (curr_vert->outgoing_edges).end(); ++itor)
    {
        (*itor)->dest->incoming_edges.Remove(*itor);
        RemoveEdge(*itor);
    }

    ReleaseContent(curr_vert);

    return true;
}

bool DirectedGraph::RemoveEdge(UniqueId fromid, UniqueId destid)
{
    Vertex* vert_from = FindById(fromid);
    Vertex* vert_dest = FindById(destid);
    if (vert_from==nullptr || vert_dest==nullptr)
    {
        return false;
    }

    // use a dummy edge to track
    Edge* dummy_edge = CreateEdge(vert_from, vert_dest, -1);
    Edge* edge_retrived = *(vert_from->outgoing_edges.Find(dummy_edge));
    ReleaseContent(dummy_edge);
    vert_from->outgoing_edges.Remove(edge_retrived);
    vert_dest->incoming_edges.Remove(edge_retrived);
    RemoveEdge(edge_retrived);

    return true;
}

DirectedGraph::VertexIterator DirectedGraph::vert_begin()
{
    return VertexIterator(*this, vert_head_->next_verts[0]);
}

DirectedGraph::VertexIterator DirectedGraph::vert_end()
{
    return VertexIterator(*this, nullptr);
}

DirectedGraph::EdgeIterator DirectedGraph::edge_begin()
{
    return EdgeIterator(*this, edge_head_);
}

DirectedGraph::EdgeIterator DirectedGraph::edge_end()
{
    return EdgeIterator(*this, nullptr);
}

DirectedGraph::Vertex* DirectedGraph::CreateVertex(int height)
{
    assert(0<height && height<=VERTEX_LIST_HEIGHT);

    Vertex* new_vertex = new Vertex;
    new_vertex->next_verts = new Vertex* [height];
    new_vertex->uniqueid = NextId(); // assign unique Id
    new_vertex->vert_state = nullptr;
    new_vertex->height = height;

    for (int i=0; i<height; ++i)
    {
        new_vertex->next_verts[i] = nullptr;
    }

    return new_vertex;
}

// delete but does not release vert_state and outedges
void DirectedGraph::ReleaseContent(Vertex* vert)
{
    delete [] vert->next_verts;
    delete vert;
}

void DirectedGraph::InsertVetexOrDie(Vertex* new_vert)
{
    Vertex* curr_vert = vert_head_;

    for (int idx = curr_height_-1; idx>=0; --idx)
    {
        while (curr_vert->next_verts[idx]!=nullptr && (curr_vert->next_verts[idx]->uniqueid)<(new_vert->uniqueid))
        {
            curr_vert = curr_vert->next_verts[idx];
        }
        vert_fix_[idx] = curr_vert;
    }

    // fail if duplicate uniqueids found !!!
    assert( (curr_vert->next_verts[0]!=nullptr && curr_vert->next_verts[0]->uniqueid==new_vert->uniqueid) == false );

    // increase current height if necessary
    while (curr_height_ < new_vert->height)
    {
        vert_fix_[curr_height_++] = vert_head_;
    }

    for (int idx=0; idx<(new_vert->height); ++idx)
    {
        new_vert->next_verts[idx] = vert_fix_[idx]->next_verts[idx];
        vert_fix_[idx]->next_verts[idx] = new_vert;
    }
}

DirectedGraph::Vertex* DirectedGraph::FindById(UniqueId tarid)
{
    Vertex* curr_vertex = vert_head_;
    
    for (int idx=curr_height_-1; idx>=0; --idx)
    {
        while (curr_vertex->next_verts[idx]!=nullptr && (curr_vertex->next_verts[idx]->uniqueid)<tarid)
        {
            curr_vertex = curr_vertex->next_verts[idx];
        }
    }

    curr_vertex = curr_vertex->next_verts[0];
    if (curr_vertex!=nullptr && curr_vertex->uniqueid == tarid) // found
    {
        return curr_vertex;
    }
    else
    {
        return nullptr;
    }
}

DirectedGraph::Edge* DirectedGraph::CreateEdge(Vertex* vert_from, Vertex* vert_dest, LengthType length)
{
    Edge* new_edge = new Edge;
    new_edge->from = vert_from;
    new_edge->dest = vert_dest;
    new_edge->length = length;
    new_edge->edge_state = nullptr;
    new_edge->prev_edge = nullptr;
    new_edge->next_edge = nullptr;

    return new_edge;
}

void DirectedGraph::ReleaseContent(Edge* edge)
{
    delete edge;
}

void DirectedGraph::PushFrontEdge(Edge* edge)
{
    if (edge_head_ == nullptr)
    {
        edge_head_ = edge;
    } 
    else
    {
        edge->next_edge = edge_head_;
        edge_head_->prev_edge = edge;
        edge_head_ = edge;
    }
}

void DirectedGraph::RemoveEdge(Edge* edge)
{
    if (edge == edge_head_)
    {
        edge_head_ = edge->next_edge;
    } 
    else
    {
        edge->prev_edge->next_edge = edge->next_edge;
        if (edge->next_edge != nullptr)
        {
            edge->next_edge->prev_edge = edge->prev_edge;
        } 
    }

    ReleaseContent(edge);
}

//////////////////////////////////////////////////////////////////////////
}