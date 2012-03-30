#include <iostream>
#include <ctime>
#include <vector>
#include "MovingWindowMedian.h"

namespace
{
//////////////////////////////////////////////////////////////////////////

const int WINDOW_ELEMENT_NUM = 5;

//////////////////////////////////////////////////////////////////////////
}

int main( int argc, char** argv )
{
    // using namespace augment_data_structure;
    using namespace std;

    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    vector<int> initvec;
    for (int i=0; i<WINDOW_ELEMENT_NUM; ++i)
    {
        initvec.push_back(i+1);
    }

    MovingWindowMedian mov_window(initvec);

    // Process test input
    int testRunLimit = 16; // INT_MAX/64;
    startTime = time(NULL);
    std::cout << "Tests start -------- " << std::endl << std::endl;
    for (int i=0; i<testRunLimit; ++i)
    {
        int newdata = rand()%6;
        mov_window.PushBack(newdata);
        std::cout << "Median at: -- " << mov_window.Median() << "  with new data: " << newdata << std::endl;
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << std::endl << "FINISHING TEST -----------------------------" << std::endl << std::endl;
    std::cout << "Test done used time:   " << timeDiff << std::endl << std::endl;

    return 0;
}