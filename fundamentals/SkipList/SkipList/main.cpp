#include <iostream>
#include "rand_height_generator.h"
#include "skip_list_set.h"
#include "skip_list_test.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    int height = RandHeight<10, 4>::Instance().RandomHeight();

    cout << "a random height returns: " << height << endl;

    const int TEST_NUM = 7;
    const int ELEMENT_NUM =  16;
    for (int j=0; j<TEST_NUM; ++j)
    {
        SkipListSet<int*, 10> ptr_set;
        int number_array[ELEMENT_NUM];
        for (int i=0; i<ELEMENT_NUM; ++i)
        {
            number_array[i] = i;
            ptr_set.Insert(&number_array[i]);
        }

        for (int i=0; i<ELEMENT_NUM; ++i)
        {
            int** valptr = ptr_set.Find( &(number_array[i]) );
            if ( !(valptr!=nullptr && (*valptr)==(&(number_array[i]))) )
            {
                cout << "skip list find error!!!!" << endl;
            }
        }
        ptr_set.Remove( &(number_array[rand()%ELEMENT_NUM]) );

        SkipListSet<int*, 10>::iterator skip_itor = ptr_set.begin();

        for (int i=0; i<ELEMENT_NUM-1; ++i)
        {
            int irand = rand();

            int* skip_value = *skip_itor++;
            if ( (*skip_value)<0 || ELEMENT_NUM<(*skip_value))
            {
                cout << "Data Not match!!!!" << endl;
            }
        }
    }


    SkipListTester pre_tester;
    pre_tester.StartTest();

    return 0;
}