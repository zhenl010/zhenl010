// Question: Find the maximum rectangle (in terms of area) under a histogram in linear time.
// http://www.informatik.uni-ulm.de/acm/Locals/2003/html/histogram.html
// It can also be used to solve the maximum rectangle problem in a matrix of (0/1)
#include <string>
#include <iostream>
#include <vector>

#include "maximal_rectangle.h"

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "result_output.txt";

//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
// MAIN ENTRY
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) 
{
    using namespace std;
    using namespace maximal_rectangle;

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

    Histogram<int> histgram;
    // Histogram<long long int> histgram;
    // Histogram<double> histgram;

    // Read data from file
    histgram.ReadFromFile(inputFileName);

    // Processed automatically within the class after read-in

    // Output to file
    histgram.WriteToFile(outputFilename);

    return 0;
}