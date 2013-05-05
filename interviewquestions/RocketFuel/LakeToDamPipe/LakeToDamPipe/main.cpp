#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <memory>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Terrain {
public:
  static const int kHeightNum = 10; // discretized height
  static const int kMaxN = 128*1024; // max map size
  static const int kInfinity = INT_MAX;

  Terrain(int m, int n, char elev[])
    : m_(m), n_(n){ copy(elev, elev+m*n, elevations_); }

  // notice x0, y0, x1, y1 start from one
  vector<pair<int,int> > GetLakeToDamPath(int x0, int y0, int x1, int y1) {
    return GetPath(x0-1, y0-1, x1-1, y1-1);
  }
  int GetCost(int h0, int h1) { return h0<h1 ? h1-h0 : h0-h1; }

private:
  struct Node {
    int idx; int from; int mincost; int costs[kHeightNum];
    Node(): idx(0), from(-1), mincost(kInfinity) {
      fill_n(costs, kHeightNum, kInfinity);
    }
  };
  struct LessCost {
    bool operator() (const Node& a, const Node& b) const {
      return b.mincost < a.mincost; // less cost higher priority
    }
  };

  typedef priority_queue<Node, vector<Node>, LessCost> NodeQueue;

  vector<pair<int,int> > GetPath(int x0, int y0, int x1, int y1);
  int GetIndex(int x, int y) { return x * n_ + y; }
  int GetX(int idx) { return idx / n_; } // row as x
  int GetY(int idx) { return idx % n_; } // col as y
  vector<int> GetNbors(int idx);
  void UpdateAt(int idx, vector<Node> &nodes, NodeQueue &actives);

  int m_; // number of rows
  int n_; // number of cols
  char elevations_[kMaxN]; // in [0...9]
};

vector<pair<int,int> > Terrain::GetPath(int x0, int y0, int x1, int y1) {
  vector<Node> nodes(m_*n_, Node());
  for (int i=0; i<m_*n_; ++i) { nodes[i].idx = i; }

  priority_queue<Node, vector<Node>, LessCost> actives;
  int lake = GetIndex(x0, y0);
  int dam = GetIndex(x1, y1);
  nodes[lake].idx = lake;
  nodes[lake].from = lake;
  nodes[lake].mincost = 0;
  for (int i=0; i<=elevations_[lake]; ++i) {nodes[lake].costs[i]=0; }
  actives.push(nodes[lake]);

  vector<pair<int,int> > path;
  while (!actives.empty() && actives.top().mincost!=kInfinity) {
    Node node = actives.top();
    actives.pop();
    ///@TODO: use customized priority with change_key operation
    if (node.mincost == nodes[node.idx].mincost) {
      if (node.idx ==8)
      {
        bool debug_here = true;
        int cost = nodes[node.idx].mincost;
        ++cost;
      }
      UpdateAt(node.idx, nodes, actives);
    }
  }

  vector<int> pathids;
  int from = dam;
  while (from!=nodes[from].from && from!=lake) {
    pathids.push_back(from);
    from = nodes[from].from;
  }
  if (from != lake) return path; // impossible path

  path.push_back(pair<int, int>(x0+1, y0+1));
  for (auto itr = pathids.rbegin(); itr!=pathids.rend(); ++itr) {
    path.push_back(pair<int, int>(GetX(*itr)+1, GetY(*itr)+1));
  }

  return path;
}

vector<int> Terrain::GetNbors(int idx) {
  int x = GetX(idx);
  int y = GetY(idx);
  vector<int> nbors;
  if (0 <= x-1) { nbors.push_back(GetIndex(x-1, y)); }
  if (0 <= y-1) { nbors.push_back(GetIndex(x, y-1)); }
  if (x+1 < m_) { nbors.push_back(GetIndex(x+1, y)); }
  if (y+1 < n_) { nbors.push_back(GetIndex(x, y+1)); }
  return nbors;
}

void Terrain::UpdateAt(int idx, vector<Node> &nodes, NodeQueue &actives) {
  vector<int> nbors = GetNbors(idx);
  for (auto nbor : nbors) {
    // dynamic programming save tentative cost at each height
    int nborcost = nodes[nbor].mincost;
    for (int i=0; i<kHeightNum; ++i) {
      if (nodes[idx].costs[i] != kInfinity) {
        int mincost = nodes[idx].costs[i];
        // find "free" water flow cost
        for (int j=i+1; j<kHeightNum; ++j) {
          mincost = min(mincost, nodes[idx].costs[j]);
        }
        int cost = mincost + GetCost(elevations_[nbor], i);
        nodes[nbor].costs[i] = min(nodes[nbor].costs[i], cost);
        nodes[nbor].mincost = min(nodes[nbor].mincost, cost);
      }
    }

    // push to queue if there's cost change
    if (nodes[nbor].mincost < nborcost) {
      nodes[nbor].from = idx;
      actives.push(nodes[nbor]);
    }
  }
}

//@TODO: change to more dynamic input like files or streams
Terrain* CinTerrain(int m, int n) {
  assert(m*n < Terrain::kMaxN);
  char elevation[Terrain::kMaxN];
  int idx = 0;
  char e;
  for (int i=0; i<m; ++i) {
    for (int j=0; j<n; ++j) {
      cin >> e;
      elevation[idx++] = e - '0'; // save relative height
    }
  }

  return new Terrain(m, n, elevation);
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int case_num, m, n, x0, y0, x1, y1;
    
  for (cin >> case_num; case_num>0; --case_num) {
    cin >> m >> n >> x0 >> y0 >> x1 >> y1;
    unique_ptr<Terrain> terrain_ptr(CinTerrain(m, n));
    vector<pair<int, int> > path = terrain_ptr->GetLakeToDamPath(x0, y0, x1, y1);
    // print path
    for (auto itr=path.begin(); itr!=path.end(); ++itr) {
      cout << itr->first << ", " << itr->second << endl;
    }
    cout << endl << endl;
  }

  return 0;
}