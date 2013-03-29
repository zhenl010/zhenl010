#include "dfs_solution.h"
#include <iostream>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

//////////////////////////////////////////////////////////////////////////
}

Solution::Solution(int vert_num, int edge_num)
    :vert_num_(vert_num), edge_num_(edge_num), vertices_(vert_num) {    
}

void Solution::AddEdge(int x, int y) { // describing that job x needs to be done before job y.
    vertices_[y-1].parents.push_back(x-1);
}

bool Solution::SortOut() {
    for(int i=0; i<vert_num_; ++i) {
        sort(vertices_[i].parents.begin(), vertices_[i].parents.end());
    }

    for(int i=0; i<vert_num_; ++i) {
        if(!Visit(i)) return false;
    }
    return true;
}

void Solution::PrintFirstSequence() {
    for(size_t i=0; i<sequence_.size(); ++i) {
        cout << sequence_[i]+1 << " ";
    }
    cout << endl;
}

bool Solution::Visit( int id ) {
    if(vertices_[id].status == kIntern) return false; // NOT A DAG!!!

    if(vertices_[id].status == kNever) {
        vertices_[id].status = kIntern;
        vector<int>& depends = vertices_[id].parents;
        for (size_t i=0; i<depends.size(); ++i) {
            if(!Visit(depends[i])) return false;
        }

        sequence_.push_back(id);
        vertices_[id].status = kDone;
    }

    return true;
}