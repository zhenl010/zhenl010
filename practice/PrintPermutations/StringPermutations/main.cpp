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

typedef std::string StringType;

void PrintPermutations(std::vector<StringType>&, unsigned int);
void PrintStringArray(const std::vector<StringType>&);

void PrintAllPermutations(std::vector<StringType>& arrayNoDup)
{
    PrintPermutations(arrayNoDup, 0);
}

void PrintPermutations(std::vector<StringType>& arrayNoDup, unsigned int idx)
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

void PrintStringArray(const std::vector<StringType>& strArray)
{
    for (std::vector<StringType>::const_iterator itor = strArray.begin(); itor!=strArray.end(); ++itor)
    {
        std::cout << *itor;
    }
    std::cout << std::endl;
}

int main()
{
    using namespace std;

    vector<StringType> arrayNoDup;
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