//////////////////////////////////////////////////////////////////////////
//  * From Cracking the Coding Interview, 5th edition 
//  * Problem 4.2
//  *
//  * Given a directed graph, design an algorithm to find out 
//  * whether there is a route between two nodes.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <queue>
#include "directed_graph.h"
#include "vertex_iterator.h"
#include "edge_iterator.h"
#include "nbor_iterator.h"


bool RouteExist(augment_data_structure::DirectedGraph::UniqueId fromid,
                augment_data_structure::DirectedGraph::UniqueId destid,
                augment_data_structure::DirectedGraph& graph)
{
    using namespace std;
    using namespace augment_data_structure;

    struct Marker
    {
        enum MARKED_STATES
        {
            NEVER,
            INPROCESS,
            DONE
        };

        MARKED_STATES marker; 
    };
    Marker vert_markers[3] = { { Marker::NEVER }, { Marker::INPROCESS }, { Marker::DONE } };

    // mark all nodes as never processed
    for (DirectedGraph::VertexIterator vtor=graph.vert_begin(); vtor!=graph.vert_end(); ++vtor)
    {
        vtor.VoidPtr() = &vert_markers[0];
    }

    queue<DirectedGraph::VertexIterator> vtor_queue;
    vtor_queue.push(graph.VertexItorById(fromid));

    bool found_route = false;
    while (vtor_queue.empty()==false && found_route==false)
    {
        DirectedGraph::VertexIterator curr_vtor = vtor_queue.front();
        if (destid == curr_vtor.VertexId())
        {
            found_route = true;
        }
        else
        {
            vtor_queue.pop();
            for (DirectedGraph::NborIterator etor=curr_vtor.outgoing_begin(); etor!=curr_vtor.outgoing_end(); ++etor)
            {
                DirectedGraph::VertexIterator nbor = etor.VertexIterator();

                Marker::MARKED_STATES vert_state = (static_cast<Marker*>(nbor.VoidPtr()))->marker; 
                if (vert_state == Marker::NEVER)
                {
                    nbor.VoidPtr() = &vert_markers[1];
                    vtor_queue.push(nbor);
                }
            }
        }

        curr_vtor.VoidPtr() = &vert_markers[2];
    }

    // set back state pointers
    for (DirectedGraph::VertexIterator vtor=graph.vert_begin(); vtor!=graph.vert_end(); ++vtor)
    {
        vtor.VoidPtr() = nullptr;
    }

    return found_route;
}

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    const int test_num = 1; // INT_MAX;
    const int vertex_num = 15;

    for (int i=0; i<test_num; ++i)
    {
        DirectedGraph test_graph;

        for (int i=0; i<vertex_num; ++i)
        {
            test_graph.NewVertex();
        }

        for (int i=2; i<vertex_num-2; ++i)
        {
            test_graph.AddEdge(i+1, i+2, 1);
            test_graph.AddEdge(i+1, i-1, 1);
        }
      
        test_graph.RemoveEdge(3, 1);
        test_graph.RemoveVertex(vertex_num/2);

        cout << "After vertex removal: " << endl;
        for (DirectedGraph::VertexIterator vtor=test_graph.vert_begin(); vtor!=test_graph.vert_end(); ++vtor)
        {
            cout << vtor.VertexId() << endl;
        }
        cout << "end of graph vertices IDs: " << endl << endl;

        cout << "After vertex removal: " << endl;
        for (DirectedGraph::EdgeIterator etor=test_graph.edge_begin(); etor!=test_graph.edge_end(); ++etor)
        {
            DirectedGraph::UniqueId FromVertexId();
            DirectedGraph::UniqueId DestVertexId();

            cout << etor.FromVertexId() << "  ===>  " << etor.DestVertexId() << endl;
        }
        cout << "end of graph edges' IDs: " << endl << endl;

        int fromid = 3;
        int destid = 6;
        if (RouteExist(fromid, destid, test_graph))
        {
            cout << "Route Exist!" << endl;
        } 
        else
        {
            cout << "Route does NOT exist!!!" << endl;
        }

        int fardestid = 10;
        if (RouteExist(fromid, fardestid, test_graph))
        {
            cout << "Route Exist!" << endl;
        } 
        else
        {
            cout << "Route does NOT exist!!!" << endl;
        }
    }

    return 0;
}