#include "Solution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl;

    // tester !!!
    Solution solver;

    // read input file and process along
    ifstream inFile(inputFileName, ios::in);
    if (inFile.is_open())
    {
        string line_str, result_str;
        // Read in line by line
        while (getline(inFile, line_str) && getline(inFile, result_str))
        {
            size_t lfpos = line_str.find_first_not_of("[");
            size_t rtpos = line_str.find_first_of("]");
            string num_str = line_str.substr(lfpos, rtpos-lfpos);
            stringstream line_stream(num_str);
            int num;
            vector<int> vec_one;
            while (line_stream >> num)
            {
                vec_one.push_back(num);
            }

            size_t prev_pos = line_str.find_first_of("[", rtpos);
            lfpos = line_str.find_first_not_of("[", prev_pos);
            rtpos = line_str.find_first_of("]");
            num_str = line_str.substr(lfpos, rtpos-lfpos);
            line_stream.clear();
            line_stream.str(num_str);
            vector<int> vec_two;
            while (line_stream >> num)
            {
                vec_two.push_back(num);
            }

            double expected;
            stringstream resultstrm(result_str);
            resultstrm >> expected;

            // explicitly make copy here (might not be necessary)
            int size_one = vec_one.size();
            int* arry_one = new int[size_one];
            for (int i=0; i<size_one; ++i)
            {
                arry_one[i] = vec_one[i];
            }
            int size_two = vec_two.size();
            int* arry_two = new int[size_two];
            for (int i=0; i<size_two; ++i)
            {
                arry_two[i] = vec_two[i];
            }

            // test test test
            double median = solver.findMedianSortedArrays(arry_one, size_one, arry_two, size_two);
            if (median != expected)
            {
                cout << "Result not as expected!!!" << endl;
            }

            delete [] arry_two;
            delete [] arry_one;
        }

        inFile.close();
    }

    return 0;
}