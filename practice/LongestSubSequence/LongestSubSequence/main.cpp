#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "longest_common_subsequence.h"

namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "result_lcs.txt";

// Helper function to keep the console window open
void press_enter_to_close()
{
    do
    {
        std::cout << "Press the ENTER key" << std::endl;
    } while(std::cin.get() != '\n');
}

//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
// MAIN ENTRY
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) 
{
    using namespace std;
    using namespace longest_common_subsequence;

    string inputFileName;
    string outputFilename;

    outputFilename = DEFAULT_OUTPUT_FILENAME;
    if (argc < 2) 
    {
        cout << "Usage: blah.exe filename.xxx" << endl;
        cout << "USING DEFAULT INPUT FILE: " << DEFAULT_INPUT_FILENAME << endl;
        inputFileName = DEFAULT_INPUT_FILENAME;
    }
    else
    {
        cout << "importing FILE: " << argv[1] << endl;
        inputFileName = argv[1];

        if (argc == 3)
        {
            outputFilename = argv[2];
        }
    }
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl;

    vector<string> twoStrs(2);
    // read two strings from file
    // 1st line defines the 1st string
    // then discard the second line (might be an empty line)
    // 3rd line defines the 2nd string
    ifstream inFile(inputFileName, ifstream::in);
    if (inFile.is_open())
    {
        if (getline(inFile, twoStrs[0]))
        {
            if (getline(inFile, twoStrs[1]))
            {
                getline(inFile, twoStrs[1]);
            }
        }

        inFile.close();
    }

    string lcs_result = LongestCommonSubquence(twoStrs[0], twoStrs[1]);
    string lcs_lean = LongestCommonSubquenceLean(twoStrs[0], twoStrs[1]);

    ofstream outfile(outputFilename);
    if (outfile.is_open())
    {
        outfile << twoStrs[0] << endl;
        outfile << twoStrs[1] << endl;
        outfile << "The longest common subsequence is: " << endl;
        outfile << lcs_result << endl;
        outfile << "The longest common subsequence is: " << endl;
        outfile << lcs_lean;
        outfile.close();
    } 

#ifdef _DEBUG
    press_enter_to_close();
#endif

    return 0;
}