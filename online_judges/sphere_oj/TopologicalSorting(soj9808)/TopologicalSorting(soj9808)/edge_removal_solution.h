#ifndef EDGE_REMOVAL_SOLUTION_H__
#define EDGE_REMOVAL_SOLUTION_H__

#include <vector>

class EdgeRemovalSolution
{
private:
    struct Node {
        Node(): num_in(0) {}
        int num_in;
        std::vector<int> children;
    };

public:
    explicit EdgeRemovalSolution(int, int);
    void AddEdge(int, int);
    bool SortOut();
    void PrintFirstSequence();

private:
    int vert_num_;
    int edge_num_;
    std::vector<Node> nodes_;
    std::vector<int> sequence_;
};

#endif