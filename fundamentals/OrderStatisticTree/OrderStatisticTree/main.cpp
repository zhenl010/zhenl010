#include <iostream>
#include "OrderStatisticTree.h"

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

bool IntLess(const int& a, const int& b) {
  return a < b;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int n, k;
  while (true) {
    n = rand() % 10000 + 10000;
    k = rand() % 5000 + 5000;

    OrderStatisticTree<int, IntLess> ostree;
    for (int i=1; i<=n; ++i) {
      ostree.Insert(i);
    }

    int rank = 0;
    while (0 < ostree.Size()) {
      rank = (--rank + k) % ostree.Size() + 1;
      int id = ostree.Select(rank--);
      // printf("%d ", id);
      ostree.Delete(id);
    }
    // printf("\n");
  }

  return 0;
}