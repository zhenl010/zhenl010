#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace // unnamed namespace
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

    //////////////////////////////////////////////////////////////////////////
    // ios_base::openmode
    // flag value	opening mode
    // app	(append) Set the stream's position indicator to the end of the stream before each output operation.
    // ate	(at end) Set the stream's position indicator to the end of the stream on opening.
    // binary	(binary) Consider stream as binary rather than text.
    // in	(input) Allow input operations on the stream.
    // out	(output) Allow output operations on the stream.
    // trunc	(truncate) Any current content is discarded, assuming a length of zero on opening.
    // These constants are defined in the ios_base class as public members. Therefore, they can be refered to
    // either directly by their name as ios_base members (like ios_base::in) or by using any of their inherited
    // classes or instantiated objects, like for example ios::ate or cout.out.
    //////////////////////////////////////////////////////////////////////////

    // read input file and process along
    ifstream inFile(inputFileName, ios::in);
    if (inFile.is_open())
    {
        string line_str;
        // Read in line by line
        while (getline(inFile, line_str))
        {
            stringstream line_stream(line_str);

            string haystr;
            line_stream >> haystr;
        }

        inFile.close();
    }

    // write to output file
    ofstream outfile(outputFilename, ios::out);
    if (outfile.is_open())
    {
        int i = 0;
        // for (; i<msgs.size(); ++i)
        {
            outfile << "Case #" << i << ": " << rand() << endl;
        }

        outfile.close();
    }

    //////////////////////////////////////////////////////////////////////////
    // Reading and Writing Complex Data
    // Although the read and write methods accept a char* pointer, there is no requirement
    // that the data you read and/or write be held in a char array. You can read or write
    // complex data objects using simple type casting of pointers:
    //////////////////////////////////////////////////////////////////////////

    class DemoType {
        int    key;
        double value;
    };

    DemoType x;
    DemoType *y = new DemoType[10];

    fstream myFile ("data.bin", ios::in | ios::out | ios::binary);

    long location;
    location=myFile.tellp();
    myFile.seekp (location);
    myFile.write ((char*)&x, sizeof (DemoType));
    //...
    myFile.seekg (0);
    myFile.read ((char*)y, sizeof (DemoType) * 10);

    // get length of file:
    // is.seekg (0, ios::end);
    // length = is.tellg();
    // is.seekg (0, ios::beg);

    return 0;
}