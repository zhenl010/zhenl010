//////////////////////////////////////////////////////////////////////////
//  * From Cracking the Coding Interview, 5th edition 
//  * Problem 4.2
//  *
//  * Given a directed graph, design an algorithm to find out 
//  * whether there is a route between two nodes.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "directed_graph.h"
#include "rand_height_generator.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    int height = VertexHeight<10, 4>::Instance().RandomHeight();

    const int test_num = INT_MAX;
    const int vertex_num = 5;

    for (int i=0; i<test_num; ++i)
    {
        vector<DirectedGraph::UniqueId> graph_vertices;
        DirectedGraph test_graph;

        for (int i=0; i<vertex_num; ++i)
        {
            test_graph.NewVertex();
        }

        for (int i=1; i<vertex_num-2; ++i)
        {
            test_graph.AddEdge(i+1, i+2, 1);
            test_graph.AddEdge(i+1, i-2, 1);
        }

        for (int i=0; i<vertex_num; ++i)
        {
            if (!test_graph.RemoveVertex(i+1))
            {
                cout << i << "th vertex Removal failed ..........." << endl;
            }
        }
    }

    return 0;
}