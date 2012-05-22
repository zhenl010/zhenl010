// Multiply Strings
//     Given two numbers represented as strings, return multiplication of the numbers as a string.
// 
// Note: The numbers can be arbitrarily large and are non-negative.
#include <iostream>
#include <string>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(*num1.begin()=='0' || *num2.begin()=='0') return string(1, '0');

        string number(num1.size()+num2.size(), '0');
        char carry = 0;
        int numsize = number.size();
        for(int i=num1.size()-1; i>=0; --i) {
            int idx = numsize-num1.size()+i;
            for(int j=num2.size()-1; j>=0; --j, --idx) {
                char tmp = carry+(num1[i]-'0')*(num2[j]-'0') + number[idx]-'0';
                carry = tmp/10;
                number[idx]='0'+ tmp%10;
            }

            while (carry>0) {
                carry = carry + number[idx] - '0';
                number[idx] = '0'+ carry%10;
                carry = carry / 10;
                --idx;
            }
        }

        return *number.begin()=='0' ? number.substr(1, number.size()-1) : number;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    string strone = "123";
    string strtwo = "456";

    string result = solver.multiply(strone, strtwo);

    return 0;
}