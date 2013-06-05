#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

int IntPower(int a, int b) {
  if (b<0) return 1/IntPower(a, -b);

  int ans = 1;
  while (b>0) {
    if (b&1) { ans *= a; }
    b >>= 1;
    a *= a;
  }
  return ans;
}

class Solution {
public:
  double pow(double x, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n<0) return 1.0 / pow(x, -(1+n)) / x;

    double ans = 1.0;
    while(0<n) {
      if (n&1) { ans *= x; }
      n >>= 1;
      x *= x;
    }

    return ans;
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  for (int i=0; i<10000; ++i) {
    int x = rand() % 100;
    int y = rand() % 20;
    int z = IntPower(x, y);
    int z0 = pow(x, y);
    if (z != z0) {
      std::cout << "ERROR " << x << " " << y << std::endl;
    }
  }

  return 0;
}