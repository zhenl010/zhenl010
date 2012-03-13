#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const long long int FB_MODULO = 4207849484;

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

struct squis_message
{
    int max;
    std::string msg;
};

// Constraints:
//     5 <= N <= 25
//     2 <= M <= 255
//     1 <= length of encoded status <= 1000

void RotateSquishes(std::vector<long long int>& squish_numbers, long long int squish_num)
{
    for (int i=static_cast<int>(squish_numbers.size())-1; i>0; --i)
    {
        squish_numbers[i] = squish_numbers[i-1];
    }
    squish_numbers[0] = squish_num;
}

long long int SquishedPossibility(const squis_message& message)
{
    using namespace std;

    stringstream mstr;
    mstr << message.max;
    int m_digits = mstr.str().size();

    vector<long long int> suffix_squish_nums(m_digits, 1);
    for (int i=static_cast<int>(message.msg.size())-1; i>=0; --i)
    {
        long long int squish_num = 0;
        if (message.msg[i] != '0') // Not supposed to start with '0'
        {
            for (int j=0; j<m_digits && i+j<static_cast<int>(message.msg.size()); ++j)
            {
                stringstream digitstr;
                digitstr << message.msg.substr(i, j+1);
                int value;
                digitstr >> value;
                if (0<value && value<=message.max)
                {
                    squish_num += suffix_squish_nums[j];
                }
                else
                {
                    suffix_squish_nums[j] = 0; // invalid case
                }
            }
        }
        RotateSquishes(suffix_squish_nums, squish_num);
    }

    return suffix_squish_nums[0];
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char **argv)
{
    using namespace std;

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

    // Read input file
    ifstream inFile(inputFileName, ifstream::in);
    vector<squis_message> msgs;
    if (inFile.is_open())
    {
        string line_str;
        int case_num;
        // Read in case number
        if (getline(inFile, line_str))
        {
            stringstream line_stream(line_str);
            line_stream >> case_num;
        }

        // read in each case
        msgs.resize(case_num);
        for (int i=0; i<case_num && getline(inFile, line_str); ++i)
        {
            stringstream line_stream(line_str);
            line_stream >> msgs[i].max;

            getline(inFile, line_str);
            msgs[i].msg = line_str;
        }

        inFile.close();
    }

    // Write process result to output
    ofstream outfile(outputFilename);
    if (outfile.is_open())
    {
        for (unsigned int i=0; i<msgs.size(); ++i)
        {
            outfile << "Case #" << i << ": " << SquishedPossibility(msgs[i]) << endl;
        }

        outfile.close();
    }
    
    return 0;
}