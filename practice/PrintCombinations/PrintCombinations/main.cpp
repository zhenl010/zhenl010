// Implement a function that prints all possible combinations of the characters in a string. 
//     These combinations range in length from one to the length of the string. 
//     Two combinations that differ only in ordering of their characters are the same combination. 
//     In other words, “12” and “31” are different combinations from the input string “123”, but “21” is the same as “12”. 
#include <iostream>
#include <string>
#include <vector>

namespace generic_combinations
{
//////////////////////////////////////////////////////////////////////////
typedef std::string DataType;

//________________________________________________________________________
// PROTOTYPES:
//________________________________________________________________________
void PrintAllCombinations(const std::vector<DataType>&);
void PrintCombinations(std::vector<std::vector<DataType>::size_type>&, std::vector<DataType>::size_type, const std::vector<DataType>&, std::vector<DataType>::size_type);
void PrintOut(const std::vector<std::vector<DataType>::size_type>&, std::vector<DataType>::size_type, std::vector<DataType>::size_type, const std::vector<DataType>&);

//________________________________________________________________________
// IMPLEMENTATIONS:
//________________________________________________________________________

void PrintAllCombinations(const std::vector<DataType>& arrayNoDup)
{
    std::vector<std::vector<DataType>::size_type> outputs(arrayNoDup.size());
    PrintCombinations(outputs, 0, arrayNoDup, 0);
}

void PrintCombinations(std::vector<std::vector<DataType>::size_type>& outputs,
    std::vector<DataType>::size_type startIdxIn,
    const std::vector<DataType>& arrayNoDup,
    std::vector<DataType>::size_type endIdxOut)
{
    for (std::vector<DataType>::size_type idx=startIdxIn; idx<arrayNoDup.size()-1; ++idx)
    {
        outputs[endIdxOut++] = idx;
        PrintOut(outputs, 0, endIdxOut, arrayNoDup);

        PrintCombinations(outputs, idx+1, arrayNoDup, endIdxOut);

        --endIdxOut;
    }

    outputs[endIdxOut++] = arrayNoDup.size()-1;
    PrintOut(outputs, 0, endIdxOut, arrayNoDup);
    --endIdxOut;
}

void PrintOut(const std::vector<std::vector<DataType>::size_type>& idxArray,
    std::vector<DataType>::size_type startIdx,
    std::vector<DataType>::size_type endIdx,
    const std::vector<DataType>& dataArray)
{
    for (std::vector<DataType>::size_type idx=startIdx; idx<endIdx; ++idx)
    {
        std::cout << dataArray[idxArray[idx]];
    }
    std::cout << std::endl;
}

// NOTE: this problem can also be solved using loops over all elements as true/false (just loops, no recursion)
// 任意重重循环: (mitbbs version, not personal favorite lolz)
void multi_loop(int *from, int *to, int n,
    void (*callback)(const int *, int)) {
        int *i = new int[n];
        int k;
        for (k = 0; k < n; k++) {
            i[k] = from[k];
        }
        do {
            (*callback)(i, n);
            for (k = 0; k < n && ++i[k] > to[k]; k++) {
                i[k] = from[k];
            }
        } while (k < n);
        delete[] i;
}

template <typename T, typename F>
void multi_loop(const T* from, const T* to, int n, F f)
{
    T* i=new T[n];
    std::copy(from, from+n, i);
    int k;
    do {
        f(i);
        for (k = 0; k < n && ++i[k] > to[k]; i[k] = from[k], k++);
    } while (k<n);
    delete [] i;
}

//________________________________________________________________________
// PROTOTYPES:
//________________________________________________________________________
void PrintAllCombinationsClean(const std::vector<DataType>&);
void PrintOut(std::vector<int>&, const std::vector<DataType>&);

//________________________________________________________________________
// IMPLEMENTATIONS:
//________________________________________________________________________

void PrintAllCombinationsClean(const std::vector<DataType>& arrayNoDup)
{
    std::vector<int>::size_type length = arrayNoDup.size();
    std::vector<int> fromVec(length, 0);
    std::vector<int> toVec(length, 1);
    std::vector<int> selectVec(length, 0);

    std::vector<int>::size_type curDigit;
    do 
    {
        PrintOut(selectVec, arrayNoDup);
        for (curDigit=0;
            curDigit<length && ++selectVec[curDigit]>toVec[curDigit];
            selectVec[curDigit] = fromVec[curDigit], ++curDigit);
    } while (curDigit<length);
}

void PrintOut(std::vector<int>& selectVec, const std::vector<DataType>& dataArray)
{
    for (std::vector<DataType>::size_type idx=0; idx<selectVec.size(); ++idx)
    {
        if (selectVec[idx] == 1)
        {
            std::cout << dataArray[idx];
        }
    }
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
}



int main()
{
    using namespace std;
    using namespace generic_combinations;

    vector<DataType> arrayNoDup;
    arrayNoDup.push_back("w");
    arrayNoDup.push_back("x");
    arrayNoDup.push_back("y");
    arrayNoDup.push_back("z");

    cout << "////////////////" << endl;
    cout << "////RECURSIVE VERSION////" << endl;
    cout << "////////////////" << endl;

    PrintAllCombinations(arrayNoDup);

    cout << "////////////////" << endl;
    cout << "////LOOP VERSION/////" << endl;
    cout << "////////////////" << endl;

    PrintAllCombinationsClean(arrayNoDup);

    return 0;
}