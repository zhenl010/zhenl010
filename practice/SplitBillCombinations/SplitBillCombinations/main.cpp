#include <iostream>
#include <string>
#include <sstream>
#include "big_integer.h"
#include "split_bill_combinations.h"

namespace { // unnamed
//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_data_structure;
using namespace split_bill_combinations;
const unsigned int TEST_NUMBER_SIZE = BillCombinationNumber::BIG_NUMBER_SIZE;

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    BillCombinationNumber billcomber;
    cout << billcomber.FindNumWays(100) << endl;
   
    return 0;
}