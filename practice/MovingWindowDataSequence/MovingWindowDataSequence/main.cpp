#include <iostream>
#include <ctime>
#include "heaped_median_window.h"

namespace
{
//////////////////////////////////////////////////////////////////////////

typedef int DataType;
struct SequenceElement
{
    DataType data;
    (SequenceElement*) *ptr;
};

const int WINDOW_ELEMENT_NUM = 3;
SequenceElement circular_array[WINDOW_ELEMENT_NUM];
SequenceElement* index_xheap[WINDOW_ELEMENT_NUM];

//////////////////////////////////////////////////////////////////////////
}

int main( int argc, char** argv )
{
    using namespace augment_data_structure;

    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    // Init
    for (int i=0; i<WINDOW_ELEMENT_NUM; ++i)
    {
        circular_array[i].ptr = &index_xheap[i];
        index_xheap[i] = &circular_array[i];
    }

    // Process test input
    int testRunLimit = 16; // INT_MAX/64;
    startTime = time(NULL);
    std::cout << "Tests start -------- " << std::endl << std::endl;
    for (int i=0; i<testRunLimit; ++i)
    {
//         // augTestSet.Insert(i);
//         bool itmFound = augTestSet.Contains(i);
//         if (itmFound == false)
//         {
//             std::cout << "CANT FIND --" << std::endl;
//         }
//         int median;
//         augTestSet.GetNthItm(2, median);
//         std::cout << "Median at: -- " << median << std::endl;
    }
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Test done used time:   " << timeDiff << std::endl << std::endl;
    std::cout << "FINISHING TEST -----------------------------" << std::endl << std::endl;

    return 0;
}