#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

// Only works for the specific problem
typedef int IdType;
const int kMaxN = 100000; // max number of user ids
const int kDnum = 2;
const int kDs[kDnum] = { 0, 1 };
int NextD (int d) { return kDs[(d+1)%kDnum]; }

struct User { IdType id; int pt[kDnum]; };

long long int DistSquare(const int pt0[kDnum],
                         const int pt1[kDnum]) {
  long long int dx = pt0[0]-pt1[0];
  long long int dy = pt0[1]-pt1[1];
  return dx*dx + dy*dy;
}

template <typename T, int N>
int ArraySize(T(&a)[N]) { return N; }

struct CoordFunctor {
  CoordFunctor(int d): dimension(d) {}
  bool operator()(const User& a, const User& b) const {
    return a.pt[dimension] < b.pt[dimension];
  }
  int dimension;
};

static const CoordFunctor CoordCompare[] = {
  CoordFunctor(0), CoordFunctor(1)
};

// Only works for the specific problem
class UserManager {
public:
  UserManager(int n, User users[]);
  vector<IdType> GetNbors(unsigned int nbor_num, const int pt[kDnum]);

private:
  // notice this definition is static and only works for the specific problem
  static const int kNullIdx = -1; // null index
  static const int kL = 0;
  static const int kR = 1;
  static int TheOtherSide(int side) { return 1-side; }
  struct Node {
    int user_idx;
    int nexts[2]; // children's indices
  };

  struct Nbor { long long int ds; IdType id; };
  struct NborCompare {
    bool operator() (const Nbor& a, const Nbor& b) const {
      if (a.ds != b.ds) return (a.ds < b.ds);
      return (b.id < a.id);
    }
  };

  void ConstructTree(int *idxptr, int l, int r, int d);
  typedef priority_queue<Nbor, vector<Nbor>, NborCompare> NborQueue;
  void GetNearestNbors(unsigned int num, const int pt[kDnum],
                       int idx, int d, NborQueue &nborqueue);

  int n_;
  User users_[kMaxN];
  Node kdtree_[kMaxN];
};

UserManager::UserManager(int n, User users[])
:n_(n) {
  std::copy(users, users+n, users_);
  Node init_node = { kNullIdx, {kNullIdx, kNullIdx} };
  std::fill_n(kdtree_, n_, init_node);
  int idx = 0;
  ConstructTree(&idx, 0, n_-1, 0);
}

vector<IdType> UserManager::GetNbors(unsigned int nbor_num, const int pt[kDnum]) {
  NborQueue nbors;
  GetNearestNbors(nbor_num, pt, 0, 0, nbors);

  vector<IdType> nborids(nbor_num);
  for (auto itr= nborids.rbegin(); itr!=nborids.rend(); ++itr) {
    *itr = nbors.top().id;
    nbors.pop();
  }
  return nborids;
}

void UserManager::ConstructTree(int *idxptr, int l, int r, int d) {
  int node_idx = *idxptr;
  int mid = l+(r-l)/2;
  // nth_element the range [first,last); last is users_+r+1 here
  std::nth_element(users_+l, users_+mid, users_+r+1, CoordCompare[d]);
  kdtree_[node_idx].user_idx = mid;

  int nexts[2][2] = { {l, mid-1}, {mid+1, r} }; // binary split
  for (int i=0; i<2; ++i) {
    if (nexts[i][0]<=nexts[i][1]) {
      *idxptr = *idxptr + 1;
      kdtree_[node_idx].nexts[i] = *idxptr;
      ConstructTree(idxptr, nexts[i][0], nexts[i][1], NextD(d));
    }
  }
}

void UserManager::GetNearestNbors(unsigned int num, const int pt[kDnum],
                                  int idx, int d, NborQueue &nborqueue) {
  if (idx==kNullIdx) return;

  long long int ds = (pt[d] - users_[kdtree_[idx].user_idx].pt[d]);
  int side = (ds<0) ? kL : kR;
  GetNearestNbors(num, pt, kdtree_[idx].nexts[side], NextD(d), nborqueue);

  if (nborqueue.size()<num || ds*ds<=nborqueue.top().ds) {
    Nbor nbor = {
      DistSquare(pt, users_[kdtree_[idx].user_idx].pt),
      users_[kdtree_[idx].user_idx].id
    };
    nborqueue.push(nbor);
    if (num < nborqueue.size()) { nborqueue.pop(); }

    GetNearestNbors(num, pt,
                    kdtree_[idx].nexts[TheOtherSide(side)],
                    NextD(d),
                    nborqueue);
  }
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int n, q, id, x, y;
  if (scanf("%d %d", &n, &q) == 2) {
    User users[kMaxN];
    for (int i=0; i<n; ++i) {
      scanf("%d %d %d", &id, &x, &y);
      User user = { id, x, y };
      users[i] = user;
    }

    const int kNborNum = 2;
    UserManager mgr(n, users);
    int coord[kDnum];
    for (int i=0; i<q; ++i) {
      scanf("%d %d", &(coord[0]), &(coord[1]));
      vector<IdType> nbors = mgr.GetNbors(kNborNum, coord);
      printf("%d %d\n", nbors[0], nbors[1]);
    }
  }

  return 0;
}