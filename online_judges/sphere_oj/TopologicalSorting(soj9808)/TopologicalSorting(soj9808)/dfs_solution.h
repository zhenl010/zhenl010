#ifndef DFS_SOLUTION_H__
#define DFS_SOLUTION_H__

#include <vector>

class Solution {
public:
    Solution(int, int);
    void AddEdge(int, int);
    bool SortOut();
    void PrintFirstSequence();

private:
    enum Status { kNever, kIntern, kDone };
    struct Node {
        Node() : status(kNever) {}
        Status status;
        std::vector<int> parents;
    };

    bool Visit(int id);

    std::vector<Node> vertices_;
    int vert_num_;
    int edge_num_;
    std::vector<int> sequence_;
};

#endif