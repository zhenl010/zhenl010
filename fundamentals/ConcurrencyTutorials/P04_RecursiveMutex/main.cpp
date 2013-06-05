#include <iostream>
#include <thread>
#include <mutex>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

std::recursive_mutex mutex;
struct Complex {
  double a; // real part
  double b; // imaginary part

  void Add(Complex z) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    a = a + z.a;
    b = b + z.b;
  }

  void Mul(Complex z) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    double c = a*z.a - b*z.b;
    double d = b*z.a + a*z.b;
    a = c;
    b = d;
  }

  // x * z1 + z2
  void Twt(Complex z1, Complex z2) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    Mul(z1);
    Add(z2);
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Complex z1 = { 1.0, 2.0 };
  Complex z2 = { 3.0, 4.0 };
  Complex z = { 0.5, 0.5 };
  z.Twt(z1, z2);

  return 0;
}