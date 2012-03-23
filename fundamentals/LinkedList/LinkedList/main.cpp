#include <iostream>
#include <string>
#include <list>

#include "singlely_linked_list.h"
#include "singlely_linked_list_iterator.h"

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

using namespace augment_data_structure;

void CoutToLine(augment_data_structure::SinglelyLinkedList<int>& list)
{
    typedef augment_data_structure::SinglelyLinkedList<int>::iterator SinglelyLinkedIterator;

    // singlely_list.MakeUniqueViaHashing();
    for (SinglelyLinkedIterator my_itor = list.begin(); my_itor!=list.end(); ++my_itor)
    {
        std::cout << *my_itor << "  ";
    }
    std::cout << std::endl;
}

void AddDigits(SinglelyLinkedList<int>& result, SinglelyLinkedList<int>& lone, SinglelyLinkedList<int>& ltwo)
{
    typedef augment_data_structure::SinglelyLinkedList<int>::iterator SinglelyLinkedIterator;
    SinglelyLinkedIterator it_one = lone.begin();
    SinglelyLinkedIterator it_two = ltwo.begin();

    int carry = 0;
    while (it_one!=lone.end() && it_two!=ltwo.end())
    {
        int digit = carry + *it_one++ + *it_two++;
        carry = digit / 10;
        digit = digit % 10;
        result.PushBack(digit);
    }

    if (it_one != lone.end())
    {
        while (it_one!=lone.end())
        {
            int digit = carry + *it_one++;
            carry = digit / 10;
            digit = digit % 10;
            result.PushBack(digit);
        }
    } 
    else
    {
        while (it_two!=ltwo.end())
        {
            int digit = carry + *it_two++;
            carry = digit / 10;
            digit = digit % 10;
            result.PushBack(digit);
        }
    }
}

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

    using namespace augment_data_structure;
    typedef SinglelyLinkedList<int> SinglelyLinkedList;
    typedef SinglelyLinkedList::iterator SinglelyLinkedIterator;
    SinglelyLinkedList lone;
    SinglelyLinkedList ltwo;

    const int MAX_EMEMENT_NUM = 10;

    for (int i=0; i<(rand() % MAX_EMEMENT_NUM); ++i)
    {
        int rand_int = rand() % 10;
        lone.PushBack(rand_int);
    }
    for (int i=0; i<(rand() % MAX_EMEMENT_NUM); ++i)
    {
        int rand_int = rand() % 10;
        ltwo.PushBack(rand_int);
    }

    CoutToLine(lone);
    CoutToLine(ltwo);

    SinglelyLinkedList lsum;
    AddDigits(lsum, lone, ltwo);
    CoutToLine( lsum );

    return 0;
}