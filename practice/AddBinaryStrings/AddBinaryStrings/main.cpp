//////////////////////////////////////////////////////////////////////////
// Given two binary strings, return their sum (also a binary string).
// Easy algorithm but tricky edge conditions @@
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string str( max(a.size(), b.size()), '\0' );
        bool carry = false;
        for(int idx=a.size()-1, j=b.size()-1, k=max(idx,j); idx>=0 && j>=0; --idx, --j, --k)
        {
            if(carry==false)
            {
                if(a[idx]=='1' && b[j]=='1')
                {
                    carry = true;
                    str[k] = '0';
                }
                else if(a[idx]=='0' && b[j]=='0')
                {
                    str[k] = '0';
                }
                else
                {
                    str[k] = '1';
                }
            }
            else
            {
                if(a[idx]=='0' && b[j]=='0')
                {
                    carry = false;
                    str[k] = '1';
                }
                else if(a[idx]=='1' && b[j]=='1')
                {
                    str[k] = '1';
                }
                else
                {
                    str[k] = '0';
                }
            }
        }

        string* pstr = a.size() < b.size() ? &b : &a;

        int idx = a.size() < b.size() ? b.size()-a.size()-1 : a.size()-b.size()-1;
        while (idx>=0)
        {
            if (carry == true)
            {
                if( (*pstr)[idx]=='0' )
                {
                    str[idx] = '1';
                    carry = false;
                }
                else
                {
                    str[idx] = '0';
                }
            } 
            else
            {
                str[idx] = (*pstr)[idx];
            }
            --idx;
        }

        if(carry)
        {
            str = '1' + str;
        }

        return str;
    }
};

int main()
{
    Solution solver;

    string tester = solver.addBinary("101111", "10");

    return 0;
}