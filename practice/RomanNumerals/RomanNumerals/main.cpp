#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    static const int SYMBOL_NUM = 7;
    static const int SYMBOL_VALUES[SYMBOL_NUM];
    static const char ROME_SYMBOLS[SYMBOL_NUM];

private:
    int romanvalues[CHAR_MAX-CHAR_MIN+1];

public:
    Solution() {
        for (int i=0; i<SYMBOL_NUM; ++i) {
            romanvalues[ROME_SYMBOLS[i]] = SYMBOL_VALUES[i];
        }
    }

    int romanToInt(string s) {
        int intval = 0;
        int pos = 0;
        int strsize = s.size();
        while (pos < strsize) {
            if (pos+1<strsize && romanvalues[s[pos+1]]>romanvalues[s[pos]]) {
                intval += romanvalues[s[pos+1]]-romanvalues[s[pos]];
                pos += 2;
            } else {
                intval += romanvalues[s[pos]];
                ++pos;
            }
        }
        return intval;
    }

    string intToRoman(int num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        string result;

        int major = SYMBOL_NUM-1;
        int minor = ((major-1)/2)*2;
        while (num>0 && minor>=0)
        {
            while (num >= SYMBOL_VALUES[major])
            {
                result += ROME_SYMBOLS[major];
                num -= SYMBOL_VALUES[major];
            }

            // MINUS possibility?
            if (minor<major && (num >= SYMBOL_VALUES[major] - SYMBOL_VALUES[minor]))
            {
                result += ROME_SYMBOLS[minor];
                result += ROME_SYMBOLS[major];
                num = num+SYMBOL_VALUES[minor]-SYMBOL_VALUES[major];
                major = minor;
                minor = ((major-1)/2)*2;
            }
            else
            {
                --major;
                minor = ((major-1)/2)*2;
            }
        }

        return result;
    }
};

const int Solution::SYMBOL_VALUES[SYMBOL_NUM] = { 1, 5, 10, 50, 100, 500, 1000 };
const char Solution::ROME_SYMBOLS[SYMBOL_NUM] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };

int main(int argc, char** argv)
{
    using namespace std;

    Solution solver;
    for (int i=1; i< 4000; ++i)
    {
        string romanstr = solver.intToRoman(i);
        int intval = solver.romanToInt(romanstr);
        cout << romanstr << "  :  " << intval << endl;
        if (i != intval)
        {
            cout << "ERROR CONVERTING!!!!" << endl;
        }
    }

    return 0;
}