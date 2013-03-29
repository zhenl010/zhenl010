#include <cstdio>
#include <cstring>

#pragma warning(disable: 4996)

namespace {
//////////////////////////////////////////////////////////////////////////

// problem specific consts
static const short MAX_COLOR = 8001;
static const short MAXN = 8002;
static const short TREE_SIZE = 16*1024;

class Solution {
public:
    Solution();
    void Reset();
    void UpdateRange(short l, short r, short val);
    void UpdateAll();
    void PrintOutCount();

private:
    struct Node { short l; short r; bool is_new; short val; }; ///@TODO: is_new not needed

    short GetChild(short idx) { return idx<<1; }
    bool IsLeaf(short idx) { return tree_[idx].l==tree_[idx].r; }
    void Construct(short idx, short l, short r);
    void UpdateRangeAt(short idx, short l, short r, short val);
    void UpdateAllFrom(short idx);
    void GetCount();

    short count_[MAX_COLOR+1]; // notice COLOR_NUMS
    short color_[MAXN];
    Node tree_[TREE_SIZE];
};

Solution::Solution() {
    Construct(1, 0, MAXN); // tree starts from index of one!
}

void Solution::Reset() {
    memset(color_, 0, sizeof(color_));
    memset(count_, 0, sizeof(count_));
    for (short i=0; i<TREE_SIZE; ++i) {
        tree_[i].val = MAX_COLOR;
        tree_[i].is_new = false;
    }
}

void Solution::UpdateRange(short l, short r, short val) {
    UpdateRangeAt(1, l, r, val);
}

void Solution::UpdateAll() {
    UpdateAllFrom(1);
    GetCount();
}

void Solution::PrintOutCount() {
    for (short i=0; i<MAX_COLOR; ++i) {
        if(count_[i]>0) printf("%d %d\n", i, count_[i]);
    }
    printf("\n");
}

void Solution::Construct(short idx, short l, short r) {
    tree_[idx].l = l;
    tree_[idx].r = r;
    if(l==r) return;

    short child = GetChild(idx);
    Construct(child, l, l+((r-l)>>1));
    Construct(child+1, l+((r-l)>>1)+1, r);
}

void Solution::UpdateRangeAt(short idx, short l, short r, short val) {
    if(l<=tree_[idx].l && tree_[idx].r<=r) {
        tree_[idx].is_new = true;
        tree_[idx].val = val;
        return;
    }

    if(tree_[idx].r<l || r<tree_[idx].l) return; // no intersect case
    if(tree_[idx].is_new && tree_[idx].val==val) return; // nothing need to be done

    short child = GetChild(idx);
    if(tree_[idx].is_new) { // repainting situation?
        tree_[child].is_new = true;
        tree_[child].val = tree_[idx].val;
        tree_[child+1].is_new = true;
        tree_[child+1].val = tree_[idx].val;
    }
    UpdateRangeAt(child, l, r, val);
    UpdateRangeAt(child+1, l, r, val);
    tree_[idx].is_new = false; // done propogation
}

void Solution::UpdateAllFrom(short idx) {
    if(IsLeaf(idx)) {
        color_[tree_[idx].l] = tree_[idx].val; // actual color update here!
        tree_[idx].is_new = false;
        return;
    }

    short child = GetChild(idx);
    if(tree_[idx].is_new) {
        tree_[child].is_new = true;
        tree_[child].val = tree_[idx].val;
        tree_[child+1].is_new = true;
        tree_[child+1].val = tree_[idx].val;
    }
    UpdateAllFrom(child);
    UpdateAllFrom(child+1);

    tree_[idx].is_new = false;
}

void Solution::GetCount() {
    ++count_[color_[0]];
    for (short i=1; i<MAXN; ++i) {
        if(color_[i]!=color_[i-1]) ++count_[color_[i]];
    }
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
    int n;
    Solution solver;
    while(scanf("%d", &n) != EOF) {
        solver.Reset();
        for (int i=0; i<n; ++i) {
            int x1, x2, c;
            scanf("%d %d %d", &x1, &x2, &c);
            solver.UpdateRange(x1, x2-1, c);
        }
        solver.UpdateAll();
        solver.PrintOutCount();
    }
    return 0;
}