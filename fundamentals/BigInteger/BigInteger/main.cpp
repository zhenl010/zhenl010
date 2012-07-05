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
    string strintA = "1234567890123456789012";
    string strintB = "987654321987654321098";
    BigInt<TEST_NUMBER_SIZE> bigintA;
    bigintA.ReadIn(strintA);
    BigInt<TEST_NUMBER_SIZE> bigintB;
    bigintB.ReadIn(strintB);
    BigInt<TEST_NUMBER_SIZE> mulproduct = bigintA * bigintB;
    string strproduct = mulproduct.String();
    if (strproduct != "1219326312467611632493760095208585886175176") {
        cout << "WRONG!!!" << endl;
    }

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