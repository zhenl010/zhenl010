#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "result_lis.txt";

// Helper function to keep the console window open
void press_enter_to_close()
{
    do
    {
        std::cout << "Press the ENTER key" << std::endl;
    } while(std::cin.get() != '\n');
}

typedef std::vector<double> SequenceType;

//////////////////////////////////////////////////////////////////////////
// reference: http://en.wikipedia.org/wiki/Longest_increasing_subsequence
// reference: http://www.alice-dsl.net/clemens.groepl/Genomanalyse/pub/longest_increasing_subsequence_2.pdf
//////////////////////////////////////////////////////////////////////////
template <typename T>
typename std::vector<T>::size_type LisBinarySearch(const std::vector<T>& sequence, 
    const std::vector< typename std::vector<T>::size_type>& helper_indices,
    typename std::vector<T>::size_type index, int length)
{
    // binary search might cause negative indices
    std::vector<T>::size_type position = 0; // j
    for (int upper_index = length, lower_index = 0; (upper_index < lower_index) == false;)
    {
        int middle_index = lower_index + (upper_index - lower_index) / 2;
        if (sequence[ helper_indices[middle_index] ] < sequence[index])
        {
            position = middle_index;
            lower_index = middle_index + 1;
        } 
        else
        {
            upper_index = middle_index - 1;
        }
    }
    return position;
}

template <typename T>
std::vector<T> LongestIncreasingSequence(const std::vector<T>& sequence)
{
    using namespace std;
    typedef vector<T> SequenceContainer;
    typedef SequenceContainer::size_type sequence_size_type;

    // early exit if empty
    if (sequence.empty()) return SequenceContainer();

    vector<sequence_size_type> helper_indices(sequence.size(), 0); // M[j]
    vector<sequence_size_type> predecessors(sequence.size(), 0); // P[k]
    sequence_size_type length = 0;
    for (sequence_size_type idx=0; idx<sequence.size(); ++idx)
    {
        // binary search might cause negative indices
        sequence_size_type position = LisBinarySearch(sequence, helper_indices, idx, length);

        // update minimum value needed (its index) to fulfill lis[position]
        predecessors[idx] = helper_indices[position];
        if ( (length == position) || (sequence[idx] < sequence[helper_indices[position+1]]) )
        {
            helper_indices[position+1] = idx;
            length = max(length, position+1);
        }
    }

    SequenceContainer result_sequence(length);
    sequence_size_type cur_idx = helper_indices[length];
    for (SequenceContainer::reverse_iterator re_it=result_sequence.rbegin(); re_it!=result_sequence.rend(); ++re_it)
    {
        *re_it = sequence[cur_idx];
        cur_idx = predecessors[cur_idx];
    }

    return result_sequence;
}

//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
// MAIN ENTRY
//////////////////////////////////////////////////////////////////////////

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

    SequenceType sequence;
    ifstream inFile(inputFileName, ifstream::in);
    if (inFile.is_open())
    {
        string line_str;
        while (getline(inFile, line_str, ','))
        {
            stringstream line_stream(line_str);
            double value_in;
            while (line_stream >> value_in)
            {
                sequence.push_back(value_in);
            }
        }

        inFile.close();
    }

    SequenceType lis_result = LongestIncreasingSequence<double>(sequence);

    ofstream outfile(outputFilename);
    if (outfile.is_open())
    {
        for (SequenceType::const_iterator itor=sequence.begin(); itor!=sequence.end(); ++itor)
        {
            outfile << *itor << "  ";
        }
        outfile << endl;
        outfile << "The longest increasing subsequence is: " << endl;
        for (SequenceType::const_iterator itor=lis_result.begin(); itor!=lis_result.end(); ++itor)
        {
            outfile << *itor << "  ";
        }

        outfile.close();
    } 

#ifdef _DEBUG
    press_enter_to_close();
#endif

    return 0;
}