//////////////////////////////////////////////////////////////////////////
// Knuth–Morris–Pratt algorithm
// BOYER-MOORE ALGORITHM
// bitap algorithm (also known as the shift-or, shift-and or Baeza–Yates–Gonnet algorithm)
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "string_search.h"

class Solution
{
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int m = strlen(needle);
        if (m == 0)
        {
            return haystack; // by default!!!
        }

        if (m > WORD_MAX)
        {
            // return kmp_str_search(haystack, needle, m);
            return BoyerMooreStrStr(haystack, strlen(haystack), needle, m);
        }
        else
        {
            return naiive_search(haystack, strlen(haystack), needle, m);
        }
    }
};

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////
const std::string DEFAULT_INPUT_FILENAME = "testcases.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";
//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    using namespace std;
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

    const int HAYS_SIZE = INT_MAX >> 16;
    const int PATTERN_SIZE = INT_MAX >> 16;

    Solution solver;
    // read input file and process along
    ifstream inFile(inputFileName, ifstream::in);
    if (inFile.is_open())
    {
        string line_str;
        // Read in line by line
        while (getline(inFile, line_str))
        {
            // string str;
            // stringstream line_stream(line_str);
            // if (getline(line_stream, str, '\"'))
            string delimiter = " ,;\"\t";
            string::size_type prev = line_str.find_first_of(delimiter, 0)+1;
            string::size_type curr = line_str.find_first_of(delimiter, prev);
            char haystack[HAYS_SIZE];
            if (curr!=string::npos) // && prev<curr
            {
                string str = line_str.substr(prev, curr-prev);
                memcpy(haystack, str.c_str(), str.size());
                haystack[str.size()] = '\0';
                prev = curr+1;
            }

            char needle[PATTERN_SIZE];
            prev = line_str.find_first_of(delimiter, prev)+1;
            prev = line_str.find_first_of(delimiter, prev)+1;
            curr = line_str.find_first_of(delimiter, prev);
            if (curr!=string::npos) // && prev<curr
            {
                string str = line_str.substr(prev, curr-prev);
                memcpy(needle, str.c_str(), str.size());
                needle[str.size()] = '\0';
                prev = curr+1;
            }

            char expected[HAYS_SIZE];
            prev = line_str.find_first_of(delimiter, prev)+1;
            prev = line_str.find_first_of(delimiter, prev)+1;
            curr = line_str.find_first_of(delimiter, prev);
            if (curr!=string::npos) // && prev<curr
            {
                string str = line_str.substr(prev, curr-prev);
                memcpy(expected, str.c_str(), str.size());
                expected[str.size()] = '\0';
                prev = curr+1;
            }

            char* foundpos = solver.strStr(haystack, needle);
            if (strlen(expected) != 0)
            {
                if (memcmp(foundpos, expected, strlen(expected)) != 0)
                {
                    cout << foundpos << endl;
                    cout << expected << endl;
                    cout << memcmp(foundpos, expected, strlen(expected)) << endl;
                }
            }
            else
            {
                if (foundpos != nullptr && strlen(foundpos)!=0)
                {
                    cout << "DIFFERENT NULL ARRAY!!!!!!!!!!!!!" << endl;
                    cout << foundpos << endl;
                }
            }
        }
    }

    char haystack[HAYS_SIZE];
    for (int i=0; i<HAYS_SIZE; ++i)
    {
        haystack[i] = 'a';
    }
    haystack[HAYS_SIZE-1] = '\0';

    char needle[PATTERN_SIZE];
    for (int i=0; i<PATTERN_SIZE; ++i)
    {
        needle[i] = 'a';
    }
    needle[PATTERN_SIZE-2]='b';
    needle[PATTERN_SIZE-1]='\0';

    char* foundpos = solver.strStr(haystack, needle);

    return 0;
}