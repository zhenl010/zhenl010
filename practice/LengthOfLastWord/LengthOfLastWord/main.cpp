// Given a string s consists of upper/lower-case alphabets and empty space characters ' ', 
// return the length of last word in the string.
// If the last word does not exist, return 0.
// Note: A word is defined as a character sequence consists of non-space characters only.
//       For example, 
//       Given s = "Hello World ",
//       return 5.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

class Solution {
public:
    int lengthOfLastWord(const char *s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(s==NULL || *s=='\0') return 0;

        const char* prb = s;
        int leng = 0;
        bool islast = false;
        while(*prb!='\0')
        {
            if(*prb==' ')
            {
                islast = true;
            }
            else if (islast)
            {
                leng = 1;
                islast = false;
            } 
            else
            {
                ++leng;
            }
            ++prb;
        }

        return leng;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    const char str[] = "Hello, world!";
    int leng = solver.lengthOfLastWord(str);

    return 0;
}