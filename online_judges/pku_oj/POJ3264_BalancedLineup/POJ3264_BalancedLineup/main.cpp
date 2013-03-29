#include <cstdio>
#include <algorithm>

#pragma warning (disable: 4996)

const int MAXN = 50001;
const int TREE_SIZE = 128*1024;

struct PairData { int min; int max; };
struct Node { int l; int r; PairData data; };

static PairData init_data = { INT_MAX, INT_MIN };
int cows[MAXN] = {};
Node tree[TREE_SIZE] = {};

inline int LeftChild(int idx) { return idx<<1; }
inline int RightChild(int idx) { return LeftChild(idx)+1; }

void Construct(int idx, int l, int r) {
    tree[idx].l = l;
    tree[idx].r = r;
    if (l==r) {
        tree[idx].data.min = cows[l];
        tree[idx].data.max = cows[l];
        return;
    }

    Construct(LeftChild(idx), l, l+((r-l)>>1));
    Construct(RightChild(idx), l+((r-l)>>1)+1, r);
    tree[idx].data.min = std::min(tree[LeftChild(idx)].data.min, tree[RightChild(idx)].data.min);
    tree[idx].data.max = std::max(tree[LeftChild(idx)].data.max, tree[RightChild(idx)].data.max);
}

void Query(int idx, int l, int r, PairData* data) {
    if (l<=tree[idx].l && tree[idx].r<=r) {
        data->min = std::min(data->min, tree[idx].data.min);
        data->max = std::max(data->max, tree[idx].data.max);
        return;
    }

    if (tree[idx].r<l || r<tree[idx].l) return;

    Query(LeftChild(idx), l, r, data);
    Query(RightChild(idx), l, r, data);
}

int main() {
    int n, q, l, r;
    PairData cow;

    while (scanf("%d %d", &n, &q) != EOF) {
        // in this problem reset is not necessary ...
        for(int i=1; i<=n; ++i) {
            scanf("%d", &cows[i]);
        }
        Construct(1, 1, n);
        for (int i=0; i<q; ++i) {
            scanf("%d %d", &l, &r);
            cow = init_data;
            Query(1, l, r, &cow);
            printf("%d\n", cow.max-cow.min);
        }
    }

    return 0;
}