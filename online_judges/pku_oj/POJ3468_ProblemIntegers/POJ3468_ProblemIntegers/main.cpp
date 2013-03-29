// segment tree, discretization, range update, range query
#include <cstdio>
#include <cstring> // memset
#include <algorithm> // std::copy

#pragma warning(disable: 4996)

const int  kN = 100002;
const int kTreeSize = 256*1024;

class Solution {
public:
    void Reset(int num, int pts[kN]) {
        num_ = num;
        memset(tree_, 0, sizeof(tree_));
        std::copy(pts, pts+num+1, pts_);
        Construct(1, 1, num);
    }

    void Construct(int idx, int l, int r) {
        tree_[idx].l = l;
        tree_[idx].r = r;
        if (l==r) {
            tree_[idx].sum = pts_[l];
        } else {
            Construct(LeftChild(idx), l, l+((r-l)>>1));
            Construct(RightChild(idx), l+((r-l)>>1)+1, r);
            tree_[idx].sum = tree_[LeftChild(idx)].sum + tree_[RightChild(idx)].sum;
        }
        tree_[idx].inc = 0;
    }

    void Incr(int l, int r, long long c) {
        Incr(1, l, r, c);
    }

    long long GetSum(int l, int r) {
        return GetSum(1, l, r);
    }

private:
    struct Segment {
        int l;
        int r;
        long long sum;
        long long inc;
    };

    int LeftChild(int idx) { return idx << 1; }
    int RightChild(int idx) { return LeftChild(idx) + 1; }
    bool IsLeaf(int idx) { return tree_[idx].l==tree_[idx].r; }
    bool IsInclusive(int idx, int l, int r) { return l<=tree_[idx].l && tree_[idx].r<=r; }
    void Propagate(int idx) {
        tree_[idx].sum += tree_[idx].inc*(tree_[idx].r-tree_[idx].l+1);
        if (!IsLeaf(idx)) {
            tree_[LeftChild(idx)].inc += tree_[idx].inc;
            tree_[RightChild(idx)].inc += tree_[idx].inc;
        }
        tree_[idx].inc = 0;
    }

    void Incr(int idx, int l, int r, long long c) {
        if (IsInclusive(idx, l, r)) {
            tree_[idx].inc += c;
        } else if (!(tree_[idx].r<l || r<tree_[idx].l)) {
            tree_[idx].sum += c * (1 + std::min(tree_[idx].r, r) - std::max(tree_[idx].l, l));
            Incr(LeftChild(idx), l, r, c);
            Incr(RightChild(idx), l, r, c);
        }
    }
    
    long long GetSum(int idx, int l, int r) {
        if (tree_[idx].inc != 0) Propagate(idx); // Lazy propagation

        if (IsInclusive(idx, l, r)) return tree_[idx].sum;
        if (tree_[idx].r<l || r<tree_[idx].l) return 0; // no intersection case
        return GetSum(LeftChild(idx), l, r) + GetSum(RightChild(idx), l, r);
    }

    long long num_;
    long long pts_[kN];
    Segment tree_[kTreeSize];
};

int main() {
    Solution solver;
    int N, Q, l, r, pts[kN];
    long long c;
    char ch;
    while (scanf("%d %d", &N, &Q) != EOF) {
        for (long long i=1; i<=N; ++i) {
            scanf("%d\n", &pts[i]);
        }
        solver.Reset(N, pts);
        for (long long i=0; i<Q; ++i) {
            scanf("%c", &ch);
            if (ch == 'Q') {
                scanf("%d %d\n", &l, &r);
                printf("%lld\n", solver.GetSum(l, r));
            } else if (ch == 'C') {
                scanf("%d %d %lld\n", &l, &r, &c);
                solver.Incr(l, r, c);
            }
        }
    }

    return 0;
}