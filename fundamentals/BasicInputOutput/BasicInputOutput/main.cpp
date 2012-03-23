#include <iostream>
#include <string>

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
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

    return 0;
}