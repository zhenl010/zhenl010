#include <iostream>
#include <string>

namespace
{
//////////////////////////////////////////////////////////////////////////

const int RECORD_NUM = 3;

enum DUTCH_COLORS {
    ZERO = 0,
    ONE = 1,
    TWO = 2
};

struct Record {
    DUTCH_COLORS key;
    std::string record;
};

void DutchPartition(Record recs[], int num) {
    // Dutch flag problem
    int lower_index = -1; // max index for key == ZERO
    int upper_index = RECORD_NUM; // max index for key == TWO
    // key == ONE records in { lower_index+1, upper_index-1 }
    for (int i=0; i<upper_index;) {
        if (recs[i].key == ZERO) {
            std::swap(recs[i], recs[++lower_index]);
            ++i;
        } else if (recs[i].key == TWO) {
            std::swap(recs[i], recs[--upper_index]);
        } else { // Assumed to be ONE
            ++i;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char* argv) {
    using namespace std;

    Record rec_arry[RECORD_NUM];
    rec_arry[0].key = TWO;
    rec_arry[0].record = "C";

    DutchPartition(rec_arry, RECORD_NUM);

    return 0;
}