#include "edge_removal_solution.h"
#include <iostream>
#include <vector>
#include <queue>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct LessPriority	{
    bool operator()(const int& a, const int& b) const {
        return b < a;
    }
};

//////////////////////////////////////////////////////////////////////////
}

EdgeRemovalSolution::EdgeRemovalSolution(int task_num, int depend_num)
    : vert_num_(task_num), edge_num_(depend_num) {
        nodes_.resize(vert_num_);
}

void EdgeRemovalSolution::AddEdge(int x, int y) {
    nodes_[x-1].children.push_back(y-1);
    ++nodes_[y-1].num_in;
}

bool EdgeRemovalSolution::SortOut() {
    priority_queue<int, vector<int>, LessPriority> starts;
    // queue<int> starts;
    for (int i=0; i<vert_num_; ++i)	{
        if(nodes_[i].num_in == 0) starts.push(i);
    }

    while(!starts.empty()) {
        sequence_.push_back(starts.top());
        vector<int> &nbors = nodes_[starts.top()].children;
        starts.pop();
        int pos;
        for (size_t i=0; i<nbors.size(); ++i) {
            pos = nbors[i];
            --(nodes_[pos].num_in);
            if (nodes_[pos].num_in==0) {
                starts.push(pos);
            }
        }
    }

    return sequence_.size() == vert_num_;
}

void EdgeRemovalSolution::PrintFirstSequence() {
    for (size_t i=0; i<sequence_.size(); ++i) {
        cout << sequence_[i]+1 << " ";
    }
    cout << endl;
}