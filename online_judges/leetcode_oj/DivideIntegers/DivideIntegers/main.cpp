#include <cassert>
#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
  int divide(int dividend, int divisor) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    assert(divisor!=0);
    unsigned int a = dividend<0 ? (~dividend+1) : dividend;
    unsigned int b = divisor<0 ? (~divisor+1) : divisor;
    if (dividend<0&&0<divisor || 0<dividend&&divisor<0) {
      return (1+~UintDivide(a, b));
    } else {
      return UintDivide(a, b);
    }
  }

private:
  unsigned int UintDivide(unsigned int a, unsigned int b) {
    unsigned int c=0, tmp=a, d=0;
    while (b <= a) {
      d = 0; tmp = a;
      while (b <= tmp) { ++d; tmp >>= 1; }
      c |= 1<<(d-1); a -= b<<(d-1);
    }  
    return c;
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;
  int dividend = INT_MIN;
  // int dividend = 5;
  int divisor = 1;
  // int divisor = 2;
  int z = solver.divide(dividend, divisor);

  return 0;
}