#include <iostream>
#include <string>
#include <sstream>
#include "big_integer.h"

namespace { // unnamed
//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_data_structure;
const unsigned int TEST_NUMBER_SIZE = 128;

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    // unsigned short divided by 3
    for (unsigned short snum=0; snum<USHRT_MAX; ++snum) {
        if (DivideByThree(snum) != snum/3) {
            cout << "Wrong result --- " << snum << endl;
            cout << DivideByThree(snum) << "  |  " << snum/3 << endl;
        }
    }

    // Exact division by 3
    BigInt<TEST_NUMBER_SIZE> testnum = 1;
    for (int i=1; i<=100; ++i) {
        testnum *= i;
    }
    if (testnum.String() != "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000") {
        cout << testnum << endl;
    }

    // division test
    string strintC = "766970544842443844";
    string strintD = "862664913";
    BigInt<TEST_NUMBER_SIZE> bigintC;
    bigintC.ReadIn(strintC);
    BigInt<TEST_NUMBER_SIZE> bigintD;
    bigintD.ReadIn(strintD);
    BigInt<TEST_NUMBER_SIZE> bigquot = bigintC / bigintD;
    string strquot = bigquot.String();
    if (strquot != "889071217") {
        cout << bigquot << "WRONG!!!" << endl;
    }

    // multiplication test
    string strintA = "12345678";
    string strintB = "987654321987654321098";
    BigInt<TEST_NUMBER_SIZE> bigintA;
    bigintA.ReadIn(strintA);
    BigInt<TEST_NUMBER_SIZE> bigintB;
    bigintB.ReadIn(strintB);
    BigInt<TEST_NUMBER_SIZE> mulproduct = bigintA * bigintB;
    string strproduct = mulproduct.String();
    if (strproduct != "12193262234567900223584514444") {
        cout << "WRONG!!!" << endl;
    }

    unsigned long long int testin = 65535 * 226;
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
        if ((testin*mult) != (bignum*mult)) {
            cout << "WRONG RESULT!!! CORRECT RESULT IS : " << crrt << endl;
        }
    }
   
    return 0;
}