#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>   // std::greater

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class Toy {
public:
  Toy() {}
  Toy(const vector<int>& ws) { std::copy(ws.begin(), ws.end(), weights_.begin()); }
  Toy(vector<int>&& ws) { weights_ = std::move(ws); }
  long long int Effort();

private:
  vector<int> weights_;
};

long long int Toy::Effort() {
  priority_queue<int, vector<int>, std::greater<int> > wsqueue;
  for (auto itr=weights_.begin(); itr!=weights_.end(); ++itr) {
    wsqueue.push(*itr);
  }

  long long int effort = 0;
  while (1<wsqueue.size()) {
    int cw = wsqueue.top();
    wsqueue.pop();
    cw += wsqueue.top();
    wsqueue.pop();
    effort += cw;
    wsqueue.push(cw);
  }
  return effort;
}

vector<int> ReadInWeights(int n) {
  vector<int> weights(n);
  int w;
  for (int i=0; i<n; ++i) {
    scanf("%d", &w);
    weights[i] = w;
  }

  return weights;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int num;
  if (scanf("%d", &num)==1) {
    vector<int> weights(num);
    Toy toy (ReadInWeights(num));
    printf("%lld\n", toy.Effort());
  }

  return 0;
}