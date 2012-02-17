#include <iostream>
#include <ctime>
#include <set>
#include "AugTreeSet.h"

// Helper function to keep the console window open
void press_enter_to_close()
{
    do
    {
        std::cout << "Press the ENTER key" << std::endl;
    } while(std::cin.get() != '\n');
}

int main( int argc, char** argv )
{
    using namespace augment_data_structure;

    // test case in a scope
    AugTreeSet<int> augTestSet;
    std::set<int> stdTestSet;
    int testRunLimit = INT_MAX/256;
    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    //////////////////////////////////////////////////////////////////////////
    // INSERT TESTS
    //////////////////////////////////////////////////////////////////////////
    // Insert tests -------- AugSet
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        stdTestSet.insert(i);
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "std lib set insert done used time:   " << timeDiff << std::endl;

    // Insert tests -------- AugSet
    startTime = time(NULL);
    for (int i=0; i<testRunLimit; ++i)
    {
        augTestSet.Insert(i);
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "AugSet insert done used time:   " << timeDiff << std::endl;

    //////////////////////////////////////////////////////////////////////////
    // press_enter_to_close();
    //////////////////////////////////////////////////////////////////////////

    return 0;
}