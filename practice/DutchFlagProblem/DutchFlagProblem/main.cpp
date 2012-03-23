//////////////////////////////////////////////////////////////////////////
// 一个记录数组，每个记录的关键字是0，1，2三个数中的一种，
// 要求将数组按关键字排序。要求算法是稳定排序，O(n)时间，常数空间。
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

namespace
{
//////////////////////////////////////////////////////////////////////////

const int RECORD_NUM = 3;

enum DUTCH_COLORS
{
    ZERO = 0,
    ONE = 1,
    TWO = 2
};

struct Record
{
    DUTCH_COLORS key;
    std::string record;
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char* argv)
{
    using namespace std;

    Record rec_arry[RECORD_NUM];
    rec_arry[0].key = TWO;
    rec_arry[0].record = "C";

    // Dutch flag problem
    int lower_index = -1; // max index for key == ZERO
    int upper_index = RECORD_NUM; // max index for key == TWO
    // key == ONE records in { lower_index+1, upper_index-1 }
    for (int i=0; i<upper_index;)
    {
        if (rec_arry[i].key == ZERO)
        {
            std::swap(rec_arry[i], rec_arry[++lower_index]);
            ++i;
        } 
        else if (rec_arry[i].key == TWO)
        {
            std::swap(rec_arry[i], rec_arry[--upper_index]);
        } 
        else // Assumed to be ONE
        {
            ++i;
        }
    }

    return 0;
}