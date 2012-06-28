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
    // BillCombinationNumber billcomber;
    // cout << billcomber.FindNumWays(100) << endl;

    unsigned long long int testin = 65535 * 256;
    BigInt<TEST_NUMBER_SIZE> bignum = testin;
    cout << "dividend: " << bignum << endl;
    for (int i=0; i<TEST_NUMBER_SIZE; ++i) {
        int mult = rand();
        BigInt<TEST_NUMBER_SIZE> quotient = bignum/mult;
        cout << "divisor: " << mult << " and quotient: " << quotient << endl;
        BigInt<TEST_NUMBER_SIZE> crrt = testin/mult;
        if (crrt != quotient) {
            cout << "WRONG RESULT!!! CORRECT RESULT IS : " << crrt << endl;
        }
    }
   
    return 0;
}