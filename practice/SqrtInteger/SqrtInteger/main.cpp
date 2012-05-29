#include <iostream>
#include <cmath>
#include <algorithm>

class Solution {
public:
    int sqrt(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(x<=1) return x; // undefined behavior

        return UnsignedSqrt(x);
    }

    unsigned int UnsignedSqrt(unsigned int x) {
        static const unsigned int MAX_INT_SQRT = 46340;
        unsigned int rti = x/2;
        rti = std::min(rti, MAX_INT_SQRT); // edge case
        unsigned int lfi = 1;
        while (lfi < rti) {
            unsigned int cti = rti - (rti - lfi) / 2;
            if (cti*cti < x) {
                lfi = cti;
            } else if (x < cti*cti) {
                rti = cti - 1;
            } else {
                return cti;
            }
        }
        return lfi;
    }
};

int main(int argc, char** argv)
{
    using namespace std;

    Solution solver;
    for (int i=-1; i<10; ++i)
    {
        cout << "sqrt(" << i << ") = " << solver.sqrt(i) << endl;
    }
    cout << "sqrt(" << 2147483647 << ") = " << solver.sqrt(2147483647) << endl;

    return 0;
}