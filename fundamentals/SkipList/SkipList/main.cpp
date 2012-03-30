#include <iostream>
#include "rand_height_generator.h"
#include "skip_list_set.h"
#include "skip_list_set_iterator.hpp"
#include "skip_list_test.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    int height = RandHeight<10, 4>::Instance().RandomHeight();

    cout << "a random height returns: " << height << endl;

    SkipListTester pre_tester;
    pre_tester.StartTest();

    int test_num = INT_MAX;
    int element_num =  16;
    for (int j=0; j<test_num; ++j)
    {
        SkipListSet<int, 10> test_int_set;
        for (int i=0; i<element_num; ++i)
        {
            test_int_set.Insert(i);
        }
        for (int i=0; i<element_num; ++i)
        {
            int* valptr = test_int_set.Find(i);
            if ( !(valptr!=nullptr && (*valptr)==i) )
            {
                cout << "skip list find error!!!!" << endl;
            }
        }
        test_int_set.Remove(rand()%element_num);

        // SkipListSet<int, 10>::iterator itor;
        // itor;
    }

    return 0;
}