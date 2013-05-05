//////////////////////////////////////////////////////////////////////////
// Implement regular expression matching with support for '.' and '*'.
// '.' Matches any single character.
// '*' Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).
// 
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
// 
// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "a*") → true
// isMatch("aa", ".*") → true
// isMatch("ab", ".*") → true
// isMatch("aab", "c*a*b") → true
//////////////////////////////////////////////////////////////////////////
#include <iostream>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (*p == '\0') return (*s == '\0');

        if (*(p+1) != '*') {
            return (*p==*s || (*s!='\0' && *p=='.')) && isMatch(++s, ++p);
        } else {
            while (*s!='\0' && (*s==*p || *p=='.')) {
                if (isMatch(s++, p+2)) return true;
            }
            return isMatch(s, p+2);
        }
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    char* str = "abcc";
    char* pat = ".*c";

    bool ismatch = solver.isMatch(str, pat);

    return 0;
}