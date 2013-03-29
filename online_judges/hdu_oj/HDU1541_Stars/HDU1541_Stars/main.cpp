#include <cstdio>
#include <cstring>

#pragma warning (disable: 4996)

const unsigned short STAR_NUM = 15000;
const unsigned short MAX_POS = 32002;

class Solution {
public:
    void SetNum(unsigned short num) {
        num_ = num;
        memset(tree_, 0, sizeof(tree_));
        memset(cnts_, 0, sizeof(cnts_));
    }

    void IncrAt(unsigned short x) {
        ++cnts_[Query(x)];
        Update(x, 1);
    }

    void PrintOut() {
        for (unsigned short i=0; i<num_; ++i) printf("%d\n", cnts_[i]);
    }

private:
    inline unsigned short lowbit(unsigned short idx) { return idx & (-idx); }

    void Update(unsigned short idx, unsigned short delta) {
        while (idx<MAX_POS) {
            tree_[idx] += delta;
            idx += lowbit(idx);
        }
    }

    unsigned short Query(unsigned short idx) {
        unsigned short sum = 0;
        while (idx>0) {
            sum += tree_[idx];
            idx -= lowbit(idx);
        }
        return sum;
    }

    unsigned short num_;
    unsigned short tree_[MAX_POS];
    unsigned short cnts_[STAR_NUM];
};

int main() {
    Solution solver;
    int num, x, y;
    while (scanf("%d", &num)!=EOF && num>0) {
        solver.SetNum(num);
        for (int i=0; i<num; ++i) {
            scanf("%d %d", &x, &y);
            solver.IncrAt(x+1);
        }
        solver.PrintOut();
    }

    return 0;
}