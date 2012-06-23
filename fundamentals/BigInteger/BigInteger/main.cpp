#include <iostream>
#include <string>
#include <sstream>
#include "big_integer.h"

namespace { // unnamed
//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_data_structure;

const int MAX_BILL = 10000;
const int NICKEL_VALUE = 5;
const int FACE_VALUES[] = {
    1, 5, 10, 25, 100, 500, 1000, 2000, 5000, MAX_BILL
};
const int NUM_CHOICES = sizeof(FACE_VALUES)/sizeof(FACE_VALUES[0]);

const int CONCISE_SIZE = MAX_BILL/NICKEL_VALUE;
const int CONCISE_CHOICES = NUM_CHOICES - 1;

const int BIG_NUMBER_SIZE = 120;

// recursive version very very slow!!!
BigInt<BIG_NUMBER_SIZE> FindNumWays(int val, int choices) {
    if (val<0 || choices<0) return 0;
    if (choices == 0) return 1;

    BigInt<BIG_NUMBER_SIZE> numways = FindNumWays(val, choices-1) + FindNumWays(val-FACE_VALUES[choices], choices);

    return numways;
}

BigInt<BIG_NUMBER_SIZE> FindNumWays(int totval) {
    BigInt<BIG_NUMBER_SIZE> numways[CONCISE_SIZE][CONCISE_CHOICES] = {0};

    // Init DP buffer
    for (int col=0; col<CONCISE_CHOICES; ++col) numways[0][col] = 1;
    for (int row=1; row<CONCISE_SIZE; ++row) {
        numways[row][0] = numways[row-1][0] + 1;
        for (int col=1; col<CONCISE_CHOICES; ++col) {
            int lastrow = row - FACE_VALUES[col+1] / NICKEL_VALUE;
            if (lastrow < 0) {
                numways[row][col] = numways[row][col-1];
            } else {
                numways[row][col] = numways[row][col-1] + numways[lastrow][col];
            }
        }
    }

    int required = totval / NICKEL_VALUE;
    for (int probe=CONCISE_SIZE; probe<=required; ++probe) {
        int row = probe % CONCISE_SIZE;
        int lastrow = (probe - 1) % CONCISE_SIZE;
        numways[row][0] = numways[lastrow][0] + 1;
        for (int col=1; col<CONCISE_CHOICES; ++col) {
            lastrow = (probe - FACE_VALUES[col+1] / NICKEL_VALUE) % CONCISE_SIZE;
            numways[row][col] = numways[row][col-1] + numways[lastrow][col];
        }
    }

    return numways[required%CONCISE_SIZE][CONCISE_CHOICES-1];
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    for (int val=1234567890; val<=1234567890; ++val) {
        BigInt<BIG_NUMBER_SIZE> numways = FindNumWays(val);
        string result = numways.String();
        cout << val << "  " << numways << endl;
    }
   
    return 0;
}