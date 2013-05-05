#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int buy = prices[0];
        int profit = 0;
        for (size_t i=1; i<prices.size(); ++i) {
            if (prices[i] < buy) {
                buy = prices[i];
            } else {
                profit += prices[i] - buy;
                buy = prices[i];
            }
        }
        return profit;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;
    vector<int> prices = { 1, 2 };
    int profit = solver.maxProfit(prices);

    return 0;
}