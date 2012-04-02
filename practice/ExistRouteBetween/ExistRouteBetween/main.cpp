//////////////////////////////////////////////////////////////////////////
//  * From Cracking the Coding Interview, 5th edition 
//  * Problem 4.2
//  *
//  * Given a directed graph, design an algorithm to find out 
//  * whether there is a route between two nodes.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "rand_height_generator.h"
#include "directed_graph.h"
#include "vertex_iterator.h"
#include "edge_iterator.h"
#include "nbor_iterator.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    int height = RandHeight<10, 4>::Instance().RandomHeight();

    const int test_num = INT_MAX;
    const int vertex_num = 15;

    for (int i=0; i<test_num; ++i)
    {
        vector<DirectedGraph::UniqueId> graph_vertices;
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

        int someid = 5;
        cout << " Nbors of vertex #: " << someid << " are:" <<endl;
        for (DirectedGraph::VertexIterator vtor=test_graph.vert_begin(); vtor!=test_graph.vert_end(); ++vtor)
        {
            if (vtor.VertexId() == someid)
            {
                ///@TODO: nbor iterator is not normal edge iterator lolz
                for (DirectedGraph::NborIterator etor=vtor.outgoing_begin(); etor!=vtor.outgoing_end(); ++etor)
                {
                    DirectedGraph::UniqueId FromVertexId();
                    DirectedGraph::UniqueId DestVertexId();

                    cout << vtor.VertexId() << "  ===>  " << etor.NborId() << endl;
                }
            }
        }
    }

    return 0;
}