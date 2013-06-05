// 一堆racer，每个racer有出发时间和到达时间，计算每个racer的score，规则如下 
//   ：score ＝ 所有出发比自己晚但是到达比自己早的racer数量之和，（所有的出发时间 
//   和到达时间没有重复的）要求时间复杂度o(nlgn).
#include <iostream>
#include <vector>
#include <algorithm>
#include "OrderStatisticTree.h"

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

struct Racer { int beg; int end; };

template<typename DataType, int N>
int ArraySize(DataType(&a)[N]) { return N; }

struct IdValue { int idx; int val; };
bool LessIdValue(const IdValue& a, const IdValue& b) {
  return a.val < b.val;
}

class ScoreHelper {
public:
  explicit ScoreHelper(const vector<Racer>& racers): racers_(racers) {}

  vector<int> GetScores() {
    int size = racers_.size();
    vector<IdValue> ends(size);
    for (int i=0; i<size; ++i) {
      ends[i].idx = i;
      ends[i].val = racers_[i].end;
    }
    sort(ends.begin(), ends.end(), LessIdValue);

    vector<int> scs(size);

    OrderStatisticTree<IdValue, LessIdValue> begins;
    for (int i=0; i<size; ++i) {
      int idx = ends[i].idx;
      IdValue beg = { idx, racers_[idx].beg };
      begins.Insert(beg);
      scs[idx] = ends[idx].val - begins.Rank(beg);
    }

    return scs;
  }
private:

  const vector<Racer>& racers_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int racer_num = 5;
  Racer rcs[] = {
    { 1, 100 },
    { 2, 10 },
    { 3, 4 },
    { 5, 6 },
  };
  vector<Racer> racers(rcs, rcs+ArraySize(rcs));
// for (int i=0; i<racer_num; ++i) {
//   racers[i].beg = rand();
//   racers[i].end = racers[i].beg + rand();
// }

  vector<int> scores = ScoreHelper(racers).GetScores();

  return 0;
}