#include <iostream>
#include "LeftLeanRedBlackTree.h"

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

//////////////////////////////////////////////////////////////////////////
}

int main() {
    LeftLeanRedBlackTree<int> llrb_tree;

    // insert tests
    int test_cnt = 100;
    for (int i=0; i<test_cnt; ++i) {
        llrb_tree.inorderTraversal();
        llrb_tree.insert(rand());
    }

    return 0;
}