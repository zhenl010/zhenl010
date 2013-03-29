#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

#pragma warning(disable: 4996)

const int kMaxN = 10001;
const int kPtsNum = 40002; // Notice this number is roughly four times kMaxN (not twice)
const int kTreeSize = 128*1024; // and this number need to be large enough according to kPtsNum

int poster_x[kMaxN];
int poster_y[kMaxN];
int dps_x[kMaxN];
int dps_y[kMaxN];

bool tocont = true;
struct Segment { int l; int r; int c; };
Segment segments[kTreeSize];
int pids[kPtsNum];
bool is_visible[kPtsNum];
int poster_num;
int pts_num;

inline int LeftChild(int idx) { return idx<<1; }
inline int RightChild(int idx) { return LeftChild(idx)+1; }
inline bool IsLeaf(int idx) { return segments[idx].l==segments[idx].r; }

// the eighth Mersenne prime, 2**31−1
static const int LCG_PRIME_M = 2147483647;
static const int LCG_CONST_A = 16807;
static const int LCG_CONST_Q = LCG_PRIME_M / LCG_CONST_A;
static const int LCG_CONST_R = LCG_PRIME_M % LCG_CONST_A;
int RandInt() {
    static int rand_seed_ = 1; // static random number generator seed
    rand_seed_ = LCG_CONST_A * (rand_seed_ % LCG_CONST_Q) - LCG_CONST_R * (rand_seed_ / LCG_CONST_Q);
    if (rand_seed_ <= 0) { rand_seed_ += LCG_PRIME_M; }
    return rand_seed_;
}

void Reset(int num) {
    poster_num = num;
    memset(pids, 0, sizeof(pids));
    memset(is_visible, false, sizeof(is_visible));
}

struct PointId { int x; int id; }; // id<0 means left end
bool PtsCompare(const PointId& a, const PointId& b) { return a.x < b.x; }
PointId pts[kPtsNum];

void Discretization() {
    int pos = 1;
    for (int i=1; i<=poster_num; ++i) {
        pts[pos].x = poster_x[i];
        pts[pos++].id = -i;
        pts[pos].x = poster_y[i];
        pts[pos++].id = i;
    }

    std::sort(pts, pts+pos, PtsCompare);

    int prev = 0; // from description minimum is 1 thus 0 could be origin
    pts_num = 0;
    for (int i=1; i<pos; ++i) {
        if (prev < pts[i].x) {
            ++pts_num;
            if (1 < pts[i].x-prev) ++pts_num;
            prev = pts[i].x;
        }

        if (pts[i].id < 0) {
            dps_x[-pts[i].id] = pts_num;
        } else {
            dps_y[ pts[i].id] = pts_num;
        }
    }
}

void Construct(int idx, int l, int r) {
    segments[idx].l = l;
    segments[idx].r = r;
    segments[idx].c = 0;
    if (l==r) return;

    Construct(LeftChild(idx), l, l+((r-l)>>1));
    Construct(RightChild(idx), l+((r-l)>>1)+1, r);
}

// precondition: idx is not leaf
void Propagate(int idx) {
    if (0 < segments[idx].c) {
        segments[LeftChild(idx)].c = segments[idx].c;
        segments[RightChild(idx)].c = segments[idx].c;
        segments[idx].c = 0;
    }
}

void UpdateAt(int idx, int l, int r, int c) {
    if (segments[idx].c==c || segments[idx].r<l || r<segments[idx].l) return;

    if (l<=segments[idx].l && segments[idx].r<=r) { // inclusive case
        segments[idx].c = c;
    } else {
        Propagate(idx);
        UpdateAt(LeftChild(idx), l, r, c);
        UpdateAt(RightChild(idx), l, r, c);
    }
}

void UpdateAll(int idx) {
    if (IsLeaf(idx)) {
        pids[segments[idx].l] = segments[idx].c;
    } else {
        Propagate(idx);
        UpdateAll(LeftChild(idx));
        UpdateAll(RightChild(idx));
    }
}

int GetCount(int idx) {
    int cnt = 0;
    if (0 < segments[idx].c) {
        if (is_visible[segments[idx].c]) {
            return 0;
        } else {
            is_visible[segments[idx].c] = true;
            return 1;
        }
    }

    if (!IsLeaf(idx)) {
        return GetCount(LeftChild(idx)) + GetCount(RightChild(idx));
    }

    return 0;
}

int VisibleNum() {
    if (poster_num == 0) return 0;

    Discretization();
    Construct(1, 1, pts_num);
    for (int i=1; i<=poster_num; ++i) {
        UpdateAt(1, dps_x[i], dps_y[i], i);
    }

    int num = GetCount(1); // this works!!!

    UpdateAll(1);
    for (int i=1; i<=pts_num; ++i) { // position 0 should be 0
        if (!is_visible[pids[i]]) { is_visible[pids[i]] = true; }
    }
    int cnt = 0;
    for (int i=1; i<=poster_num; ++i) { if (is_visible[i]) ++cnt; }

    if (num != cnt) {
        printf("////\n\n%d .vs. %d\n", num, cnt);
        tocont = false;
        printf("////\n\n%d\n", poster_num);
        for (int i=1; i<=poster_num; ++i) {
            printf("%d %d\n", poster_x[i], poster_y[i]);
        }
    }

    return cnt;
};

int main() {
    int case_num, n;
    for (scanf("%d", &case_num); 0<case_num; --case_num) {
        scanf("%d", &n);
        Reset(n);
        for (int i=1; i<=n; ++i) {
            scanf("%d %d", &poster_x[i], &poster_y[i]);
        }
        printf("%d\n", VisibleNum());
    }

    while (!tocont) {
        n = RandInt() % 10000 + 1;
        Reset(n);
        for (int i=1; i<=n; ++i) {
            poster_x[i] = RandInt() % 1000000 + 1;
            poster_y[i] = RandInt() % 1000000 + 1;
        }
        int cnt = VisibleNum();
    }

    return 0;
}