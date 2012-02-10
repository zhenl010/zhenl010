#include <iostream>
#include "SkipList.h"

int main()
{
    using namespace augment_data_structure;

    typedef int KeyType;
    typedef float DataType;

    KeyType aKey(1);
    DataType aData(1.23456f);

    SkipList<KeyType, DataType> testSkipList;

    int lvlDistribution[SkipList<KeyType, DataType>::MAX_LEVEL];

    srand(static_cast<unsigned int>(time(NULL)));
    for (int i=0; i<INT_MAX/128; ++i)
    {
        aKey = rand();
        testSkipList.Insert(aKey, aData);
    }

    std::cout << "Level Distribution:" << std::endl;
    for (int i=1; i<SkipList<KeyType, DataType>::MAX_LEVEL; ++i)
    {
        int numLast = lvlDistribution[i-1];
        std::cout << double(numLast)/lvlDistribution[i] << std::endl;
    }

    return 0; 
}