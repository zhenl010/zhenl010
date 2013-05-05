#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class MoneyGamble {
public:
  MoneyGamble(double p, int k): p_(p), k_(k) {}
  long long int NumRounds();
  long long int Dollars();

private:
  double p_;
  int k_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int t;
  cin >> t;
  for (int i=0; i<t; ++i) {
    double p;
    int k;
    // cin >> p >> k;
    scanf("%lf %d", &p, &k);
    MoneyGamble game(p, k);
    printf("%.0f, %.0f", 10.123, 456.789);
  }

  return 0;
}