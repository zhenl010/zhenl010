#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "cstr_delims.h"

class Solution
{
public:
    bool IsValidNumber(const char* s)
    {
        using namespace augment_lib;
        const char* probe = s;
        return augment_lib::IsValidNumber(probe);
    }
};

// ihasleetcode's code below:
bool IsNumber(const char *s)
{
    bool num = false;
    bool dot = false;   //decimal sign
    bool exp = false;   //exponential sign
    bool spa = false;   //space
    //trim spaces on left
    while(*s != '\0' && *s == ' ' ) ++s;
    //skip +/- sign
    if (*s!='\0' && (*s == '+' || *s == '-'))++s;

    while(*s != '\0')
    {
        if(*s == ' ') spa = true;
        else if(spa) return false; //space inside of non-space make number invalid

        else if (*s >= '0' && *s <= '9')
            num = true;

        else if(*s == 'e')
        {
            //exponential sign already exist, or no number in front
            //then invalid number.
            if(exp || !num) return false;
            exp = true;
            num = false; // need number after exponential sign, so make it false
        }
        else if(*s == '.')
        {
            //no decimal sign after exponential sign and decimal sign
            if(exp || dot) return false;
            dot = true;
        }
        else if(*s == '-' || *s == '+')
        {
            // +/- sign should only follow exponential sign
            if (*(s-1) != 'e') return false;
        }

        else //any other characters would make number invalid 
            return false;
        ++s;
    }

    return num;
}

namespace // unnamed
{
    //////////////////////////////////////////////////////////////////////////
    const std::string DEFAULT_INPUT_FILENAME = "default_input.txt";
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
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl << endl  << endl;

    Solution solver;

    // read input file and process along
    ifstream inFile(inputFileName, ifstream::in);
    if (inFile.is_open())
    {
        string line_str;
        // Read in line by line
        while (getline(inFile, line_str))
        {
            char* numstr = new char[line_str.size()+1];
            memcpy(numstr, line_str.c_str(), line_str.size());
            numstr[line_str.size()] = '\0';

            string expected;
            getline(inFile, expected);
            getline(inFile, expected);
            stringstream sstrm(expected);
            bool exansw;
            sstrm >> boolalpha >> exansw; // noboolalpha by default

            cout << numstr << endl;
            if (solver.IsValidNumber(numstr) != exansw)
            {
                cout << "WRONG answer!" << endl;
            }

            delete [] numstr;
        }
    }

    return 0;
}