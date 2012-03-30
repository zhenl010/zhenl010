#include "directed_graph.h"
#include <limits>
#include <cassert>
#include "rand_height_generator.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const int VERTEX_LIST_HEIGHT = 10;
const int VERTEX_LIST_PINV = 4;
const int NEIGHBOR_LIST_HEIGHT = 4;
const int NEIGHBOR_LIST_PINV = 4;

//////////////////////////////////////////////////////////////////////////
}

DirectedGraph::DirectedGraph()
: nextid_(0), curr_height_(0), edge_head_(nullptr)
{
    vert_head_ = CreateVertex(VERTEX_LIST_HEIGHT);
    vert_fix_ = new Vertex*[VERTEX_LIST_HEIGHT];
    nbor_fix_ = new EdgeRef*[NEIGHBOR_LIST_HEIGHT];
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
    delete [] nbor_fix_;

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
    int height = VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::Instance().RandomHeight();
    Vertex* new_vertex = CreateVertex(height);
    InsertVetexOrDie(new_vertex);

    return new_vertex->uniqueid;
}

bool DirectedGraph::RemoveVertex(UniqueId vid)
{
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
    if ( curr_vert!=nullptr && curr_vert->uniqueid==vid )
    {
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

        ReleaseContent(curr_vert);

        return true;
    }
    else
    {
        return false;
    }
}

void DirectedGraph::AddEdge(UniqueId fromid, UniqueId destid, LengthType length)
{
    Vertex* vert_from = FindById(fromid);
    Vertex* vert_dest = FindById(destid);
    Edge* new_edge = CreateEdge(vert_from, vert_dest, length);
    // add new edge to graph edge list
    PushFrontGraphEdges(new_edge);
    // add pointer to new edge to the edge's from vertex
    PushEdgerefToVertexFrom(new_edge);
}

DirectedGraph::Vertex* DirectedGraph::CreateVertex(int height)
{
    assert(0<height && height<=VERTEX_LIST_HEIGHT);

    Vertex* new_vertex = new Vertex;
    new_vertex->next_verts = new Vertex* [height];
    new_vertex->uniqueid = NextId(); // assign unique Id
    new_vertex->edgeref_head = nullptr;
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
//     EdgeRef* edgeref =  vert->edgeref_head;
//     while (edgeref != nullptr)
//     {
//         EdgeRef* nextref = edgeref->next;
//         delete edgeref;
//         edgeref = nextref;
//     }

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

void DirectedGraph::PushFrontGraphEdges(Edge* edge)
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

void DirectedGraph::PushEdgerefToVertexFrom(Edge* new_edge)
{
    Vertex* vert_from = new_edge->from;

    // add to vert_from's out_edge list
    EdgeRef* edgeref = new EdgeRef;
    edgeref->edge = new_edge;
    edgeref->next = nullptr;
    if (vert_from->edgeref_head == nullptr)
    {
        vert_from->edgeref_head = edgeref;
    } 
    else
    {
        edgeref->next = vert_from->edgeref_head;
        vert_from->edgeref_head = edgeref;
    }
}

//////////////////////////////////////////////////////////////////////////
}