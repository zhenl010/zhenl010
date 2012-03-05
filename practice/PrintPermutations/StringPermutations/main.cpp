// Permutations of a String
// Important:  Implement a routine that prints all possible orderings of the characters in a string. 
//             In other words, print all permutations that use all the characters from the original string. 
//             For example, given the string “hat”, your function should print the strings 
//             “tha”, “aht”, “tah”, “ath”, “hta”, and “hat”. 
//             Treat each character in the input string as a distinct character, even if it is repeated. 
//             Given the string “aaa”, your routine should print “aaa” six times. You may print the permutations
//             in any order you choose. 
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>

typedef std::string DataType;

void PrintPermutations(std::vector<DataType>&, unsigned int);
void PrintStringArray(const std::vector<DataType>&);

void PrintAllPermutations(std::vector<DataType>& arrayNoDup)
{
    PrintPermutations(arrayNoDup, 0);
}

void PrintPermutations(std::vector<DataType>& arrayNoDup, unsigned int idx)
{
    if (idx >= (arrayNoDup.size()-1))
    {
        PrintStringArray(arrayNoDup);
    } 
    else
    {
        for (unsigned int i=idx; i<arrayNoDup.size(); ++i)
        {
            swap(arrayNoDup[i], arrayNoDup[idx]);
            PrintPermutations(arrayNoDup, idx+1);
            swap(arrayNoDup[idx], arrayNoDup[i]);
        }
    }
}

void PrintStringArray(const std::vector<DataType>& strArray)
{
    for (std::vector<DataType>::const_iterator itor = strArray.begin(); itor!=strArray.end(); ++itor)
    {
        std::cout << *itor;
    }
    std::cout << std::endl;
}

int main()
{
    using namespace std;

    vector<DataType> arrayNoDup;
    arrayNoDup.push_back("a");
    arrayNoDup.push_back("b");
    arrayNoDup.push_back("c");
    arrayNoDup.push_back("d");
//     arrayNoDup.push_back("e");
//     arrayNoDup.push_back("f");

    PrintStringArray(arrayNoDup);

    cout << "////////////////" << endl;

    PrintAllPermutations(arrayNoDup);

    cout << "////////////////" << endl;

    PrintStringArray(arrayNoDup);

    return 0;
}