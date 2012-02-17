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

        if (i % 3 == 1)
        {
            int medin;
            if (augTestSet.GetNthItm(i/2+1, medin))
            {
                std::cout << "The " << i/2+1 << "th item is: " << medin << std::endl;
                if (augTestSet.Remove(medin))
                {
                    std::cout << "and removed" << std::endl;
                }
            }
        }
    }

    return 0;
}