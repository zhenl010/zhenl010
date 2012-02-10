#include <iostream>
#include "AugTreeSet.h"

int main()
{
    using namespace augment_data_structure;

    // test case in a scope
    AugTreeSet<int> augTestSet;
    for (int i=0; i<INT_MAX; ++i)
    {
        std::cout << i << std::endl;
        augTestSet.Insert(i);
    }

    return 0;
}