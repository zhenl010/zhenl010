#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if(prices.empty()) return 0;
        Bets bets = getBets(prices, 0, prices.size()-1);

        return bets.profit;
    }

private:
    struct Bets { int min; int max; int profit; };

    Bets getBets(const vector<int> &prices, int i, int j) {
        Bets bets = { prices[i], prices[i], 0 };
        if (i < j) {
            Bets leftbet = getBets(prices, i, i+(j-i)/2);
            Bets rightbet = getBets(prices, j-(j-i)/2, j);
            bets = leftbet;
            bets.min = min(bets.min, rightbet.min);
            bets.max = max(bets.max, rightbet.max);
            bets.profit = max(bets.profit, rightbet.profit);
            bets.profit = max(bets.profit, rightbet.max-leftbet.min);
        }
        return bets;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {

    return 0;
}