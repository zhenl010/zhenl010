//////////////////////////////////////////////////////////////////////////
// The set [1,2,3,…,n] contains a total of n! unique permutations.
// By listing and labeling all of the permutations in order,
// We get the following sequence (ie, for n = 3):
// "123"
// "132"
// "213"
// "231"
// "312"
// "321"
// Given n and k, return the kth permutation sequence.
// Note: Given n will be between 1 and 9 inclusive.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string str(n, '\0');
        for(int i=0; i<n; ++i) {
            str[i] = '1' + i;
        }
        
        int fac = 1;
        for(int i=2; i<n; ++i) {
            fac *= i;
        }

        --k;
        for(int i=0; i<n-1; ++i) {
            int dig = k / fac;
            if (dig > 0) {
                k = k - dig*fac;
                int idx = i + dig;
                swap(str[i], str[idx]);
                // fix sorting
                while (idx>i+1 && str[idx]<str[idx-1]) {
                    swap(str[idx], str[idx-1]);
                    --idx;
                }
                while (idx<n-1 && str[idx]>str[idx-1]) {
                    swap(str[idx], str[idx+1]);
                    ++idx;
                }
            }
            fac /= (n-i-1);
        }
        
        return str;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;
    int n = 4;
    int k = 5;

    string str = solver.getPermutation(n, k);

    return 0;
}