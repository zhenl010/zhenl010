//////////////////////////////////////////////////////////////////////////
// Knuth–Morris–Pratt algorithm
// BOYER-MOORE ALGORITHM
// bitap algorithm (also known as the shift-or, shift-and or Baeza–Yates–Gonnet algorithm)
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "string_search.h"

class Solution
{
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = strlen(needle);
        if (m >= WORD_MAX)
        {
            // return kmp_str_search(haystack, needle, m);
            return BoyerMooreStrStr(haystack, strlen(haystack)-1, needle, m);
        }

        return bitap_bitwise_search(haystack, needle, m);
    }
};

int main(int argc, char** argv)
{
    const int HAYS_SIZE = 360;
    const int PATTERN_SIZE = 7;

    char haystack[HAYS_SIZE+1] = "abbaxbabyabbfababaabbababgbbabeababbabdababbacbab";
    char pattern[PATTERN_SIZE+1] = "abbabab";

    Solution solver;
    char* foundpos = solver.strStr(haystack, pattern);

    return 0;
}