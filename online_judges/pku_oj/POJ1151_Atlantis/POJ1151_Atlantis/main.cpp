#include <cstdio>
#include <algorithm>

#pragma warning(disable: 4996)

namespace {
//////////////////////////////////////////////////////////////////////////

static const int MAXN = 256;
static const int SEG_NUM = 2048;

struct Rect { double x1; double y1; double x2; double y2; };

class AtlantisMap {
public:
    AtlantisMap(): num_(0) {}

    void Reset() { num_ = 0; }

    void AddMaps(Rect rects[], int n) {
        num_ = n;
        Discretize(rects);
    }

    double GetArea() {
        ConstructTree(1, 0, xcnt_);

        double area = 0.0f;
        double len = 0.0f;
        Update(1, edges_[0]);
        for (int i=1; i<num_*2; ++i) {
            len = GetLen(1);
            area += (edges_[i].y-edges_[i-1].y) * len;
            Update(1, edges_[i]);
        }

        return area;
    }

private:
    struct RectEdge { int l; int r; double y; char chg; }; // islow==true means bottom
    static bool HigherEdge(const RectEdge& a, const RectEdge& b) { return a.y<b.y; }
    static struct PointX { double x; int idx; }; // idx<0 means left end
    static bool ComparePointX(const PointX& a, const PointX& b) { return a.x<b.x; }

    struct Segment {
        int l; int r;
        int cnt; // overlap count, 0 means empty
        double len; // accumulated length
    };

    int LeftChild(int idx) const { return idx<<1; }
    int RightChild(int idx) const { return LeftChild(idx) | 1; }
    bool IsLeaf(int idx) const { return tree_[idx].l+1 == tree_[idx].r; }

    void ConstructTree(int idx, int l, int r) {
        Segment seg = { l, r, 0, 0.0f };
        tree_[idx] = seg;
        if ((l+1)==r) return; // notice the leaf condition
        ConstructTree(LeftChild(idx), l, l+((r-l)>>1));
        ConstructTree(RightChild(idx), l+((r-l)>>1), r);
    }

    void Discretize(Rect rects_[]) { // x1, x2 discretized
        if (num_ < 1) return;

        int id = 0;
        for (int i=1; i<=num_; ++i) { // starts from 1!
            PointX ptx1 = { rects_[i].x1, -i };
            pointx[id] = ptx1;
            edges_[id].y = rects_[i].y1;
            edges_[id].chg = 1;
            ++id;
            PointX ptx2 = { rects_[i].x2, i };
            pointx[id] = ptx2;
            edges_[id].y = rects_[i].y2;
            edges_[id].chg = -1;
            ++id;
        }
        
        std::sort(pointx, pointx+id, ComparePointX);

        xcnt_ = 0;
        double prev = (pointx[0]).x;
        xvals_[xcnt_] = prev;
        for (int i=0; i<id; ++i) {
            if (prev < pointx[i].x) {
                ++xcnt_;
                prev = pointx[i].x;
                xvals_[xcnt_] = prev;
            }

            if (pointx[i].idx < 0) {
                edges_[-2*pointx[i].idx-2].l = xcnt_;
                edges_[-2*pointx[i].idx-1].l = xcnt_;
            } else {
                edges_[2*pointx[i].idx-2].r = xcnt_;
                edges_[2*pointx[i].idx-1].r = xcnt_;
            }
        }

        std::sort(edges_, edges_+2*num_, HigherEdge);

        ///@TODO: only save unique x values according to xcnts
    }

    void Update(int idx, const RectEdge& edge) {
        if (edge.r<=tree_[idx].l || tree_[idx].r<=edge.l) return; // no intersection

        if (edge.l<=tree_[idx].l && tree_[idx].r<=edge.r) { // fully covered
            tree_[idx].cnt += edge.chg;
        } else { // partially covered (leaf node would have been fully covered
            Update(LeftChild(idx), edge);
            Update(RightChild(idx), edge);
        }

        tree_[idx].len = GetLen(idx);
    }

    double GetLen(int idx) {
        if (0 < tree_[idx].cnt) {
            return xvals_[tree_[idx].r] - xvals_[tree_[idx].l];
        } else if (tree_[idx].cnt==0) {
            if (IsLeaf(idx)) {
                return 0.0f;
            } else {
                return tree_[LeftChild(idx)].len + tree_[RightChild(idx)].len;
            }
        }
        return tree_[idx].len;
    }

    int num_;
    int xcnt_;
    PointX pointx[2*MAXN];
    double xvals_[2*MAXN];
    RectEdge edges_[2*MAXN];
    Segment tree_[SEG_NUM];
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    int n, id=0;
    AtlantisMap atlantismap;
    Rect rects_[MAXN];
    while (scanf("%d", &n)!=EOF && n!=0) {
        atlantismap.Reset();
        for (int i=1; i<=n; ++i) {
            scanf("%lf %lf %lf %lf", &rects_[i].x1, &rects_[i].y1, &rects_[i].x2, &rects_[i].y2);
        }
        atlantismap.AddMaps(rects_, n);
        printf("Test case #%d\n", ++id);
        printf("Total explored area: %.2f\n\n", atlantismap.GetArea());
    }

    return 0;
}