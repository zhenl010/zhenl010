#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        static const int SYMBOL_NUM = 7;
        static const int SYMBOL_VALUES[SYMBOL_NUM] = { 1, 5, 10, 50, 100, 500, 1000 };
        static const std::string ROME_SYMBOLS[SYMBOL_NUM] = { "I", "V", "X", "L", "C", "D", "M" };

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

int main(int argc, char** argv)
{
    using namespace std;

    Solution solver;
    for (int i=1; i< 4000; ++i)
    {
        cout << solver.intToRoman(i) << endl;
    }

    return 0;
}