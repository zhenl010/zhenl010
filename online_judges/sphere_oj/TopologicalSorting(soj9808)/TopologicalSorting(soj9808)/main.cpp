#include <iostream>
#include <vector>
// #include <set>
#include <queue>
// #include <functional>
// #include "edge_removal_solution.h"
// #include "dfs_solution.h"

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

const int MAXN = 10000;

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
    Node nodes_[MAXN];
    int sequence_[MAXN];
    int snum_;
};

struct LessPriority	{
    bool operator()(const int& a, const int& b) const {
        return b < a;
    }
};

EdgeRemovalSolution::EdgeRemovalSolution(int task_num, int depend_num)
    : vert_num_(task_num), edge_num_(depend_num), snum_(0) {
}

void EdgeRemovalSolution::AddEdge(int x, int y) {
    nodes_[x-1].children.push_back(y-1);
    ++nodes_[y-1].num_in;
}

bool EdgeRemovalSolution::SortOut() {
    priority_queue<int, vector<int>, LessPriority> starts;
    // priority_queue<int, vector<int>, greater<int> > starts;
    // queue<int> starts;
    // set<int> starts;
    for (int i=0; i<vert_num_; ++i)	{
        if(nodes_[i].num_in == 0) starts.push(i);
    }

    int curr;
    int pos;
    while(!starts.empty()) {
        curr = starts.top();
        starts.pop();
        sequence_[snum_++] = curr;
        for (size_t i=0; i<nodes_[curr].children.size(); ++i) {
            pos = nodes_[curr].children[i];
            --(nodes_[pos].num_in);
            if (nodes_[pos].num_in==0) {
                // starts.insert(pos);
                starts.push(pos);
            }
        }
    }

    return snum_ == vert_num_;
}

void EdgeRemovalSolution::PrintFirstSequence() {
    for (size_t i=0; i<snum_; ++i) {
        // cout << sequence_[i]+1 << " ";
        printf("%d ", sequence_[i]+1);
    }
    // cout << endl;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
	int task_num, depend_num;
	// std::cin >> task_num >> depend_num;
    scanf("%d %d", &task_num, &depend_num);

	EdgeRemovalSolution er_solver(task_num, depend_num);
    // Solution dfs_solver(task_num, depend_num);
	int x, y;
	for (int i=0; i<depend_num; ++i) {
		// std::cin >> x >> y;
        scanf("%d %d", &x, &y);
		er_solver.AddEdge(x, y);
        // dfs_solver.AddEdge(x, y);
	}

	if (er_solver.SortOut()) {
		er_solver.PrintFirstSequence();
    // if (dfs_solver.SortOut()) {
    //    dfs_solver.PrintFirstSequence();
	} else {
		cout << "Sandro fails." << endl;
	}

	return 0;
}