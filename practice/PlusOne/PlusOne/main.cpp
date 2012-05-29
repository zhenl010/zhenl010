//////////////////////////////////////////////////////////////////////////
// Plus One
// Given a number represented as an array of digits, plus one to the number.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace  std;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> num = digits;
        int carry = 1;
        for(int i= digits.size()-1; i>=0; --i) {
            carry += digits[i];
            num[i] = carry %10;
            carry /= 10;
        }
        if(carry>0) num.insert(num.begin(), carry);
        return num;
    }
};

int main(int argc, char** argv)
{
    return 0;
}