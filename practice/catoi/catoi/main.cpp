//////////////////////////////////////////////////////////////////////////
// Implement atoi to convert a string to an integer.
// Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask
// yourself what are the possible input cases.
// Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible
// to gather all the input requirements up front.
// Requirements for atoi:
// The function first discards as many whitespace characters as necessary until the first non-whitespace 
// character is found. Then, starting from this character, takes an optional initial plus or minus sign 
// followed by as many numerical digits as possible, and interprets them as a numerical value.
// The string can contain additional characters after those that form the integral number, which are ignored and
// have no effect on the behavior of this function.
// If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence
// exists because either str is empty or it contains only whitespace characters, no conversion is performed.
// If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range
// of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

class Solution {
public:
    int atoi(const char* str) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        const char* s = NextOfSelection(str, " ", false); // skip spaces
        if (s == NULL || *s == '\0') return 0; // no valid conversion

        bool isnegative = false;
        if (s == NextOfSelection(s, "+-", true)) { // plus minus sign
            if (*s == '-') isnegative = true;
            ++s;
        }
        if (s == NULL || *s == '\0') return 0; // no valid conversion
        const char* NUMERICAL_DIGITS = "0123456789";
        unsigned long long int num = 0;
        while (s == NextOfSelection(s, NUMERICAL_DIGITS, true) && num<ULONG_MAX/10) {
            num = num*10 + (*s - '0');
            ++s;
        }
        if (s == NextOfSelection(s, NUMERICAL_DIGITS, true)) { return isnegative ? INT_MIN : INT_MAX; }
        if (isnegative==false && num>INT_MAX) { return INT_MAX; }
        if (isnegative==true && num>(-(long long int)INT_MIN)) { return INT_MIN; }
        return isnegative ? -(int)num : (int)num;
    }

private:
    bool IsOfSelection(const char& ch, const char* sls) {
        while(*sls != '\0') {
            if (ch == *sls) return true;
            ++sls;
        }
        return false;
    }

    const char* NextOfSelection(const char* str, const char* toks, bool condition) {
        while (*str != '\0') {
            if ( IsOfSelection(*str, toks) == condition) return str;
            ++str;
        }
        return NULL;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    char* str = "      -11919730356x";
    int num = solver.atoi(str);

    return 0;
}