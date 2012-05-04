#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "longest_palindromic_substring.h"

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:

    // O(N^2) time O(1) space
    string longestPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.empty()) return string();

        int sublf = -1;
        int subrt = 1;
        for (int i=1; i<s.size(); ++i)
        {
            // odd lengthes
            int lf = i-1;
            int rt = i+1;
            while (lf>=0 && rt<s.size() && s[lf]==s[rt])
            {
                --lf; ++rt;
            }
            if (rt-lf > subrt-sublf)
            {
                sublf = lf;
                subrt = rt;
            }
            // even lengthes
            lf = i-1;
            rt = i;
            while (lf>=0 && rt<s.size() && s[lf]==s[rt])
            {
                --lf; ++rt;
            }
            if (rt-lf > subrt-sublf)
            {
                sublf = lf;
                subrt = rt;
            }
        }

        return s.substr(sublf+1, subrt-sublf-1);
    }
};

bool SameContent(const std::string& strone, const std::string& strtwo)
{
    if (strone.size() != strtwo.size()) return false;
    for (std::string::const_iterator it1=strone.begin(), it2=strtwo.begin();
        it1!=strone.end() && it2!=strtwo.end();
        ++it1, ++it2)
    {
        if (*it1 != *it2) return false;
    }
    return true;
}

const std::string DEFAULT_INPUT_FILENAME = "default_input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    using namespace std;

    Solution tester_one;
    LpsSolver tester_two;

    string inputFileName = DEFAULT_INPUT_FILENAME;
    string outputFilename = DEFAULT_OUTPUT_FILENAME;

    if (argc < 2) 
    {
        cout << "Usage: blah.exe filename.xxx" << endl;
    }
    else
    {
        inputFileName = argv[1];

        if (argc == 3)
        {
            outputFilename = argv[2];
        }
    }

    cout << "importing from FILE:   " << inputFileName  << endl;
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl;

    // read input file and process along
    ifstream inFile(inputFileName, ios::in);
    if (inFile.is_open())
    {
        string linestr;
        string palinstr;
        // Read in line by line
        while (getline(inFile, linestr))
        {
            if (getline(inFile, palinstr)) // expected result
            {
                string lpstr_one = tester_one.longestPalindrome(linestr);
                string lpstr_two = tester_two.LongestPalindrome(linestr);

                if (SameContent(lpstr_two, palinstr) == false)
                {
                    cout << linestr << endl;
                    cout << palinstr << endl;
                    cout << lpstr_two << endl;
                }
            }
        }

        inFile.close();
    }

    return 0;
}