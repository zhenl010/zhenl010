//////////////////////////////////////////////////////////////////////////
// Implement wild-card (abit different than regular expression) matching with support for '?' and '*'.
// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
// (regular expression:) '*' Matches zero or more of the preceding element.
// The matching should cover the entire input string (not partial).
// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "*") → true
// isMatch("aa", "a*") → true
// isMatch("ab", "?*") → true
// isMatch("aab", "c*a*b") → false
//////////////////////////////////////////////////////////////////////////
// Notice there's another method to do this using FFT and O(N * log(M)) !!!
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
        // return IsWildMatchClean(s, p);
        return isMatchWithStar(s,p, false);
        // return IsWildMatchGoto(s, p);
    }
private:

    //////////////////////////////////////////////////////////////////////////
    // Iterative version runs ~ same speed as longway2008?
    //////////////////////////////////////////////////////////////////////////
    bool IsWildMatchClean(const char *str, const char *pat) {
        const char* s = str;
        const char* p = pat;
        bool star = false;

        while (*s!='\0') {
            switch (*p) {
            case '?': // any char would match
                ++s;
                ++p;
                break;
            case '*': // wild card !!!
                star = true;
                while (*p == '*') { ++p; }
                if (*p == '\0') return true;
                // save current positions
                str = s;
                pat = p;
                break;
            default:
                if (*s == *p) {
                    ++s;
                    ++p;
                } else {
                    if (!star) return false;
                    // try next possible match
                    s = ++str;
                    p = pat;
                }
                break;
            } // endswitch
        } // endwhile

        while (*p == '*') { ++p; }
        return (*p == '\0');
    }

    //////////////////////////////////////////////////////////////////////////
    // Recursive version by longway2008 (very fast)
    //////////////////////////////////////////////////////////////////////////
    bool isMatchWithStar(const char *str, const char *pat, bool hasStar=false) 
    {
        if (!*pat) return !*str || hasStar;

        const char *s, *p;
        for (s = str, p = pat; *s; ++s, ++p) {
            if (*p == '*') 
                return isMatchWithStar(s, p+1, true);  
            else if ( *p != '?' && *s != *p) 
                return !hasStar ? false : isMatchWithStar(str+1, pat, hasStar);
        }

        while (*p == '*') ++p;
        return (!*p);      
    }

    bool IsWildMatchGoto(const char *str, const char *pat) {
        const char* s;
        const char* p;
        bool star = false;

loopStart:
        for (s = str, p = pat; *s!='\0'; ++s, ++p) {
            switch (*p) {
            case '?': // any char would match
                break;
            case '*': // wild card !!!
                star = true;
                str = s, pat = p;
                if (*++pat == '\0') return true;
                goto loopStart;
            default:
                if (*s != *p) { goto starCheck; }
                break;
            } // endswitch
        } // endfor
        while (*p == '*') ++p;
        return (!*p);

starCheck:
        if (!star) return false;
        str++;
        goto loopStart;
    }

    bool IsMatchRec(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (*p == '\0') return (*s == '\0');
        if (*s == '\0') return (*p == '\0' || (*p=='*' && isMatch(s, p+1)));
        if (*p=='*' && *(p+1) == '\0') { return true; } // wild match!!!

        if (*p != '*') {
            return (*p==*s || *p=='?') && isMatch(++s, ++p);
        } else {
            while (*p == '*') { // move past '*'
                ++p;
            }
            while (*s!='\0') {
                if (isMatch(s++, p)) return true;
            }
            return isMatch(s, p);
        }
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    char* str = "hi";
    char* pat = "*?";

    bool ismatch = solver.isMatch(str, pat);

    return 0;
}