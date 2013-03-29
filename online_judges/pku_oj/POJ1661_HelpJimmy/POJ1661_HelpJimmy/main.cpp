#include <cstdio>
#include <set>
#include <map>
#include <algorithm>

#pragma warning (disable: 4996)

namespace {
//////////////////////////////////////////////////////////////////////////

// problem specific consts
const int MAXN = 1001;
const int X_MIN = -20000;
const int X_MAX = 20000;
const int TREE_SIZE = 2*1024;

class Solution {
private:
    struct Segment { int x1; int x2; int y; int l; int r; int t1; int t2; };
    struct Node { int l; int r; int seg; }; // seg as the segment id, seg>=0 means is_new

    int size_;
    int x_;
    int y_;
    int d_;
    int pos_num_; // x discretized into this many parts
    int pos_;
    Segment segment_[MAXN];
    Node tree_[TREE_SIZE];

public:
    void Reset(int size, int x, int y, int d) {
        size_=1; x_=x; y_=y; d_=d; // segment_[0] as ground
        memset(segment_, 0, sizeof(segment_));
        for (int i=0; i<TREE_SIZE; ++i) {
            tree_[i].seg = 0;
        }
    }

    void Add(int x1, int x2, int h) {
        segment_[size_].x1 =x1; segment_[size_].x2 =x2; segment_[size_].y=h;
        ++size_;
    }

    // The core function that returns the answer of the problem (find the time to the ground)
    int GetTime() {
        // sort
        std::sort(segment_, segment_+size_, HeightCompare);

        // discretization:
        Discretize();
        Construct(1, 0, pos_num_);

        // dp, segment_[0] as ground
        for (int i=1; i<size_; ++i) {
            int l = GetSeg(1, segment_[i].l);
            int r = GetSeg(1, segment_[i].r);

            if (d_<segment_[i].y-segment_[l].y && d_<segment_[i].y-segment_[r].y) continue;

            if ((!(d_<segment_[i].y-segment_[l].y)) && (!(d_<segment_[i].y-segment_[r].y))) {
                segment_[i].t1 = GetTimeToSeg(segment_[i].x1, segment_[i].y, l);
                segment_[i].t2 = GetTimeToSeg(segment_[i].x2, segment_[i].y, r);
                segment_[i].t1 = std::min(segment_[i].t1, segment_[i].t2+segment_[i].x2-segment_[i].x1);
                segment_[i].t2 = std::min(segment_[i].t2, segment_[i].t1+segment_[i].x2-segment_[i].x1);
            } else if (!(d_<segment_[i].y-segment_[l].y)) {
                segment_[i].t1 = GetTimeToSeg(segment_[i].x1, segment_[i].y, l);
                segment_[i].t2 = segment_[i].t1+segment_[i].x2-segment_[i].x1;
            } else if (!(d_<segment_[i].y-segment_[r].y)) {
                segment_[i].t2 = GetTimeToSeg(segment_[i].x2, segment_[i].y, r);
                segment_[i].t1 = segment_[i].t2+segment_[i].x2-segment_[i].x1;
            }

            Update(1, segment_[i].l, segment_[i].r, i);
        }

        return GetTimeToSeg(x_, y_, GetSeg(1, pos_));
    }

private:
    static bool HeightCompare(const Segment& lhs, const Segment& rhs) { return lhs.y < rhs.y; }
    bool IsNew(int idx) { return !(tree_[idx].seg<0); }

    void Discretize() {
        std::set<int> xset;
        xset.insert(x_);
        for (int i=1; i<size_; ++i) {
            xset.insert(segment_[i].x1);
            xset.insert(segment_[i].x2);
        }

        std::map<int, int> xmap;
        pos_num_ = 1; // added two segments at the beginning and end
        for (std::set<int>::iterator itr=xset.begin(); itr!=xset.end(); ++itr) {
            xmap[*itr] = pos_num_++;
        }

        // segment_[0] as ground; added two segments at the beginning and end
        segment_[0].l = 0;
        segment_[0].r = pos_num_+1;
        for (int i=1; i<size_; ++i) {
            segment_[i].l = xmap[segment_[i].x1];
            segment_[i].r = xmap[segment_[i].x2];
        }
        pos_ = xmap[x_];
    }

    int LeftChild(int idx) { return idx<<1; }
    int RightChild(int idx) { return 1+(idx<<1); }
    bool IsLeaf(int idx) { return tree_[idx].l == tree_[idx].r; }

    void Construct(int idx, int l, int r) {
        tree_[idx].l = l;
        tree_[idx].r = r;
        if(l==r) return;

        Construct(LeftChild(idx), l, l+((r-l)>>1));
        Construct(RightChild(idx), l+((r-l)>>1)+1, r);
    }

    void Update(int idx, int l, int r, int seg) {
        if (l<=tree_[idx].l && tree_[idx].r<=r) { tree_[idx].seg = seg; return; }
        if (r<tree_[idx].l || tree_[idx].r<l) return; // no intersect case
        if (IsNew(idx) && tree_[idx].seg==tree_[idx].seg) return; // nothing to be done

        if (IsNew(idx)) { // repainting
            tree_[LeftChild(idx)].seg = tree_[idx].seg;
            tree_[RightChild(idx)].seg = tree_[idx].seg;
            tree_[idx].seg = -1; // mark is_old
        }

        Update(LeftChild(idx), l, r, seg);
        Update(RightChild(idx), l, r, seg);
    }

    int GetSeg(int idx, int x) {
        if (IsLeaf(idx)) return tree_[idx].seg;

        if (IsNew(idx)) { // repainting
            tree_[LeftChild(idx)].seg = tree_[idx].seg;
            tree_[RightChild(idx)].seg = tree_[idx].seg;
            tree_[idx].seg = -1; // mark is_old
        }

        return x>tree_[LeftChild(idx)].r ? GetSeg(RightChild(idx), x) : GetSeg(LeftChild(idx), x);
    }

    int GetTimeToSeg(int x, int y, int seg) {
        if (segment_[seg].y == 0) return y-segment_[seg].y; // reached ground

        return y-segment_[seg].y+std::min( x-segment_[seg].x1+segment_[seg].t1,segment_[seg].x2-x+segment_[seg].t2);
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    int t, n, x, y, d;
    scanf("%d", &t);
    int x1, x2, h;
    for (int i=0; i<t; ++i) {
        scanf("%d %d %d %d", &n, &x, &y, &d);
        solver.Reset(n, x, y, d);
        for (int j=0; j<n; ++j) {
            scanf("%d %d %d", &x1, &x2, &h);
            solver.Add(x1, x2, h);
        }
        printf("%d\n", solver.GetTime());
    }

    return 0;
}