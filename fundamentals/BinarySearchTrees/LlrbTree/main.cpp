#include <set>
#include "llrb_tree.h"

int main() {
  LlrbTree llrb_tree;
  std::set<int> std_set;
  // insert tests
  int test_cnt = 20000;
  int x = 0;
  llrb_tree.Insert(x);
  std_set.insert(x);
  llrb_tree.InorderTraversal();

  for (int i=0; i<test_cnt; ++i) {
    x = rand() % test_cnt;
    llrb_tree.Insert(x);
    std_set.insert(x);
  }

  while (x != test_cnt-1) {
    x = rand() % test_cnt;
    llrb_tree.Insert(x);
    llrb_tree.Remove(x);
    std_set.insert(x);
    std_set.erase(x);
  }

  while (!std_set.empty()) {
    x = *std_set.begin();
    std_set.erase(x);
    llrb_tree.Remove(x);
  }

  llrb_tree.InorderTraversal();

  return 0;
}