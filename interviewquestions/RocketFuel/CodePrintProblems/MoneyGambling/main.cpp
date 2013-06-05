#include <cmath>
#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

// p is a decimal number with at most two digits after the decimal point such that 0.6 <= p <= 1
static const double delta_ = 0.001;

class Solution {
public:
  Solution(double p, int k): p_(p), k_(k) {}
  double NumRounds();
  double Dollars();

private:
  double p_;
  int k_;
};

double Solution::NumRounds() {
  if (p_ >= 1.0-delta_) return k_;

  double p_k = pow(p_, k_);
  return (p_k-1.0)/(p_k*(p_-1.0));
}

double Solution::Dollars() {
  if (p_ >= 1.0-delta_) return k_*k_;

  double p_k = pow(p_, k_);
  return (2.0 - (3.0+2.0*k_)*p_k +p_k*p_k + (1.0+2.0*k_)*p_k*p_ - p_k*p_k*p_) / 
    (p_k*p_k*(p_-1)*(p_-1));
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int t;
  cin >> t;
  for (int i=0; i<t; ++i) {
    double p;
    int k;
    scanf("%lf %d", &p, &k);
    Solution game(p, k);
    printf("%llu", (long long unsigned int)game.NumRounds());
    printf(" %llu\n", (long long unsigned int)game.Dollars());
  }

  return 0;
}