#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable: 4996)

#include <stdio.h>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

const int MAXN = 202;

enum Status { kNever, kRed, kBlue };

class Solution {
public:
    Solution(): num_(0) {}

    void Reset(int num) {
        static Node init_node = { kNever, vector<int>() };
        num_ = num;
        for (int i=0; i<num_; ++i) {
            nodes_[i] = init_node;
        }
    }

    void AddEdge(int ppl, int enemy) {
        nodes_[ppl].enemys.push_back(enemy);
        nodes_[enemy].enemys.push_back(ppl);
    }

    int MaxNum() {
        int max_num = 0;
        for (int i=0; i<num_; ++i) {
            if (nodes_[i].status == kNever) {
                max_num += GetMaxNum(i);
            }
        }
        return max_num;
    }

private:
    struct Node {
        Status status;
        vector<int> enemys;
    };

    int GetMaxNum(int id) {
        int red_max = 0;
        int blue_max = 0;
        bool is_bipartite = true;
        GetMaxNum(id, kBlue, is_bipartite, red_max, blue_max);
        return max(red_max, blue_max);
    }

    void GetMaxNum(int id, Status st, bool &is_pipartite, int &red_num, int &blue_num) {
        if (nodes_[id].status == st) is_pipartite = false;

        if (nodes_[id].status == kNever) {
            if (st == kRed) {
                nodes_[id].status = kBlue;
                ++blue_num;
            } else {
                nodes_[id].status = kRed;
                ++red_num;
            }

            for (vector<int>::iterator itr = nodes_[id].enemys.begin(); itr != nodes_[id].enemys.end(); ++itr) {
                GetMaxNum(*itr, nodes_[id].status, is_pipartite, red_num, blue_num);
            }
        }

        if (!is_pipartite) {
            red_num = 0;
            blue_num = 0;
        }
    }

    Node nodes_[MAXN];
    int num_;
};

//////////////////////////////////////////////////////////////////////////
} // end namespace

int main() {
    int case_nums;
    int cnt = scanf("%d", &case_nums);
    Solution solver;
    int ppl_nums, enemy_num, enemy;
    for(; case_nums>0; --case_nums) {
        cnt = scanf("%d", &ppl_nums);
        solver.Reset(ppl_nums);
        for(int ppl=0; ppl<ppl_nums; ++ppl) { // starts from zero
            cnt = scanf("%d", &enemy_num);
            for(int m=0; m<enemy_num; ++m) {
                cnt = scanf("%d", &enemy);
                if(enemy<1 || ppl_nums<enemy) continue;
                solver.AddEdge(ppl, enemy-1);
            }
        }
        printf("%d\n", solver.MaxNum());
    }
}