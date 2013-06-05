// input two integers a and b, get the decimal presentation of a/b
// e.g.
// a = 4, b = 3, output 1.(3)
// a = 1, b = 2, output 0.5
// a = 5, b = 22, output 0.2(27)
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    // assume b != 0
    string decimalStr(unsigned int a, unsigned int b) {
        assert(b!=0);

        unsigned int c = a<b ? greatestCommonDivisor(b, a) : greatestCommonDivisor(a, b);
        a /= c;
        b /= c;

        stringstream sstrm;
        sstrm << a/b << decimalFraction(a%b, b);

        return sstrm.str();
    }

private:
    // assume b <= a
    unsigned int greatestCommonDivisor(unsigned int a, unsigned int b) {
        unsigned int c = a % b;
        while (c!=0) {
            a = b;
            b = c;
            c = a % b;
        }
        return b;
    }

    // assume b!=0 and a<b
    string decimalFraction(unsigned int a, unsigned int b) {
        string str;
        if (a == 0) return str;

        str += ".";
        unsigned int ids = 0;
        unordered_map<unsigned int, unsigned int> mods;
        while (a!=0 && mods.find(a)==mods.end()) {
            ++ids;
            mods[a] = ids;
            a *= 10;
            str += ('0' + a/b);
            if (b <= a) {
                a = a % b;
            }
        }

        if (a != 0) { // repetitive decimals
            str.insert(mods[a], "(");
            str += ")";
        }

        return str;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    unsigned int numerator = 7;
    unsigned int denominator = 22;
    cout << numerator << " / " << denominator << " = " << solver.decimalStr(numerator, denominator) << endl;

    return 0;
}