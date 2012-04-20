#include <iostream>
#include <cassert>

class Solution {
public:
    unsigned int UintDivide(unsigned int dividend, unsigned int divisor)
    {
        int shiftnum = 0;
        while (dividend>>shiftnum > divisor) ++shiftnum;

        int result = 0;
        while(dividend >= divisor)
        {
            if(dividend >= (divisor<<shiftnum))
            {
                result |= 1<<shiftnum;
                dividend -= divisor<<shiftnum;
            }
            --shiftnum;
        }
        return result;
    }

    int divide(int dividend, int divisor) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        assert(divisor!=0);

        if ((dividend<0 && divisor>0) || (dividend>0 && divisor<0))
        {
            return -(int)UintDivide(abs(dividend), abs(divisor));
        } 
        else
        {
            return (int)UintDivide(abs(dividend), abs(divisor));
        }
    }

    // ihasleetcode's code:
    typedef unsigned int uint;
    uint udivide(uint a, uint b) {
        uint x = 0, ret = 0;
        int numBits = sizeof(uint) * 8;
        for (int i = numBits - 1; i >= 0; i--) {
            x |= ((a >> i) & 1);
            if (x >= b) {
                ret |= 1;
                x -= b;
            }
            if (i > 0)
                ret <<= 1;
            x <<= 1;
        }
        return ret;
    }

};

int main(int argc, char** argv)
{
    Solution solver;

    // -2147483648
    int num = solver.divide( INT_MIN, 1 );

    return 0;
}