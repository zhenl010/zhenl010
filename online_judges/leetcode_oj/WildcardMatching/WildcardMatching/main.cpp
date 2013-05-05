// Implement wild-card (abit different than regular expression) matching with support for '?' and '*'.
// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
// 
// The matching should cover the entire input string (not partial).
// 
// The function prototype should be:
// bool isMatch(const char *s, const char *p)
// 
// Some examples:
// isMatch("aa","a") → false
// isMatch("aa","aa") → true
// isMatch("aaa","aa") → false
// isMatch("aa", "*") → true
// isMatch("aa", "a*") → true
// isMatch("ab", "?*") → true
// isMatch("aab", "c*a*b") → false
#include <cstring>
#include <iostream>
#include <vector>

namespace { // unnamed namespace
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    // assume s and p are not null
    bool isMatch(const char *s, const char *p) {
        if (*p=='\0') return *s=='\0';

        // remove duplicate '*'s
        char *pat = new char[strlen(p)+1];
        char* q = pat;
        int cnt = 0;
        while (*p!='\0') {
            *q = *p;
            if (*p=='*') {
                while (*p=='*') ++p;
            } else {
                ++p;
                ++cnt;
            }
            ++q;
        }
        *q = '\0'; // add string ending
        int sl = strlen(s);
        int pl = strlen(pat);
        if (sl<cnt) return false;
        bool is_match = isMatch(s, sl, pat, pl);
        delete [] pat;
        return is_match;
    }

private:
    bool isMatch(const char *s, int sl, const char *p, int pl) {
        vector<vector<bool>> matches(2, vector<bool>(sl+1, false));
        char flag = 0;
        matches[flag][sl] = true;

        int i=pl-1;
        int pos = sl-1;
        while (0<=i) {
            flag = 1 - flag;
            matches[flag] = vector<bool>(sl+1, false); // reset every time
            if (p[i]!='*') {
                for (int j=pos; 0<=j; --j) {
                    matches[flag][j] = matches[1-flag][j+1] && (p[i]=='?' || p[i]==s[j]);
                }
                --pos;
            } else { // wild case
                int k=sl;
                while (0<=k && !matches[1-flag][k]) { --k; }
                if (k<0 || (pos+1)*2<i) return false;
                for (int l=0; l<=k; ++l) matches[flag][l] = true;
            }
            --i;
        }

        return matches[flag][0];
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;
    // char* s = ""; char* p = "*";
    // char* s = ""; char* p = "ab*";
    char* s = ""; char* p = "*a*";
    // char* s = "aa"; char* p = "*";
    // char* s = "aa"; char* p = "a";
    // char* s = "b"; char* p = "?*?";
    // char* s = "abcd"; char* p = "*?*?*?*?";
    // char* s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    // char *p  = "*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*";

    bool ismatch = solver.isMatch(s, p);

    return 0;
}