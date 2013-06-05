#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template<typename DataType, int N>
int ArraySize(DataType(&a)[N]) { return N; }

unsigned long long int CoinChanges (vector<unsigned int> coins) {
  return 0;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  unsigned int vals[] = { 1, 2, 5, 10 };
  vector<unsigned int> coins(vals, vals+ArraySize(vals));

  return 0;
}