#include <iostream>
#include <vector>
#include <string>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template <typename T, int N>
int ArraySize(T(&a)[N]) { return N; }

class Solution
{
public:
  int maxProfit(vector<int> &prices) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (prices.size() < 2) return 0;

    vector<int> profits[2];
    profits[0] = FrontProfits(prices);
    profits[1] = BackProfits(prices);
    int best = 0;
    for (size_t i=0; i<prices.size(); ++i) {
      best = max(best, profits[0][i]+profits[1][i]);
    }
    return best;
  }

private:
  vector<int> FrontProfits(const vector<int> &prices) const {
    int lowest = prices[0];
    vector<int> profits(prices.size(), 0);
    for (size_t i=1; i<prices.size(); ++i) {
      profits[i] = max(profits[i-1], prices[i]-lowest);
      lowest = min(lowest, prices[i]);
    }
    return profits;
  }

  vector<int> BackProfits(const vector<int> &prices) const {
    int highest = *prices.rbegin();
    vector<int> profits(prices.size(), 0);
    for (int i=prices.size()-2; i>=0; --i) {
      profits[i] = max(profits[i+1], highest-prices[i]);
      highest = max(highest, prices[i]);
    }
    return profits;
  }
};

string RandName() {
  return "Random Name";
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;

  int arry[] = {
    1, 2
  };
  vector<int> prices(arry, arry+ArraySize(arry));

  int profit = solver.maxProfit(prices);

  //////////////////////////////////////////////////////////////////////////
  // r-value tests
  string str = RandName();
  string &lref = RandName();
  string &&rref = RandName();

  return 0;
}