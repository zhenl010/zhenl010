#include <iostream>
#include <ctime>
#include <set>
#include "adam_tree_set.h"

int main( int argc, char** argv )
{
    using namespace augment_data_structure;

    // test case in a scope
    AdamTreeSet<int> augTestSet;
    std::set<int> stdTestSet;
    int testRunLimit = INT_MAX/1024;
    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    //////////////////////////////////////////////////////////////////////////
    // INSERT TESTS
    //////////////////////////////////////////////////////////////////////////

    // Insert tests -------- AdamTreeSet
    std::cout << "Insert tests start -------- AdamTreeSet" << std::endl << std::endl;
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        augTestSet.Insert(i);
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "AdamTreeSet insert done used time:   " << timeDiff << std::endl << std::endl;

    // Insert tests -------- std::set
    std::cout << "Insert tests start -------- std::set" << std::endl << std::endl;
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        stdTestSet.insert(i);
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "std lib set insert done used time:   " << timeDiff << std::endl << std::endl;

    //////////////////////////////////////////////////////////////////////////
    // SEARCH TESTS
    //////////////////////////////////////////////////////////////////////////

    // -------- std::set
    std::cout << "SEARCH tests start -------- std::set" << std::endl << std::endl;
    std::set<int>::iterator itr;
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        itr = stdTestSet.find(rand());
        if (itr == stdTestSet.end())
        {
            std::cout << "CANT FIND --" << std::endl;
        }
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "std lib set search done used time:   " << timeDiff << std::endl << std::endl;

    //  -------- AdamTreeSet
    std::cout << "Search tests start -------- AdamTreeSet" << std::endl << std::endl;
    bool itmFound = true;
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        itmFound = augTestSet.Contains(rand());
        if (itmFound == false)
        {
            std::cout << "CANT FIND --" << std::endl;
        }
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "AdamTreeSet search done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << "FINISHING TEST -----------------------------" << std::endl << std::endl;

    return 0;
}