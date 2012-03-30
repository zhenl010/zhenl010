#include "skip_list_test.h"
#include <iostream>
#include <set>
#include <algorithm>
#include "skip_list_set.h"
#include "skip_list_set_iterator.hpp"

void SkipListTester::StartTest()
{
    using namespace std;
    using namespace augment_data_structure;
    
    cout << "Test start -------------------- " << endl;

    int test_num = INT_MAX;
    int element_num =  16;
    for (int j=0; j<test_num; ++j)
    {
        SkipListSet<int, 10> skip_set;
        set<int> std_set;
        for (int i=0; i<element_num; ++i)
        {
            skip_set.Insert(i);
            std_set.insert(i);
        }
        for (int i=0; i<element_num; ++i)
        {
            int* valptr = skip_set.Find(i);
            if ( !(valptr!=nullptr && (*valptr)==i) )
            {
                cout << "skip list find error!!!!" << endl;
            }
        }

        int randin = rand()%element_num;
        skip_set.Remove(randin);
        std_set.erase(randin);

        SkipListSet<int, 10>::iterator skip_itor = skip_set.begin();
        set<int>::iterator std_itor = std_set.begin();

        for (int i=0; i<element_num-1; ++i)
        {
            int irand = rand();

            int skip_value = *skip_itor++;
            int std_value = *std_itor++;
            if (skip_value != std_value)
            {
                cout << "Data Not match!!!!" << endl;
            }
        }
    }
}