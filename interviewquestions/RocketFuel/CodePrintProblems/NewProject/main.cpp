#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class MoneyGamble {
public:
  explicit MoneyGamble(double p): p_(p) {}
  long long int NumRounds();
  long long int Dollars();

private:
  double p_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int n, q, id, x, y;
  if (scanf("%d %q", &n, &q) == 1) {
    for (int i=0; i<n; ++i) {
      // scanf("%d %d %d", &id, &x, &y);
    }

    for (int i=0; i<q; ++i) {
      // printf("%d %d\n", nbors[0], nbors[1]);
    }
  }

  return 0;
}