//////////////////////////////////////////////////////////////////////////
// 就是输入一个n，代表二进制数有几位，然后要求打印所有n位的二进制数，但打印有个规则，就是相邻
// 两个数之间只能有一位不一样。比如n为2时，一个打印方法可以是：00 01 11 10。
// 而 00 01 10 11就不可以一位01和10有两位不一样.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

// prototypes:
void PrintBinaryAdj(int n);
void PrintCombinationsAdj(int n);
void PrintCombinations(int n);

using namespace std;

void PrintBinaryAdjt(string& str, int curr)
{
    if (curr == str.size())
    {
        cout << str << endl;
        return;
    }

    PrintBinaryAdjt(str, curr+1);
    str[curr] = (str[curr] == '0') ? '1' : '0';
    PrintBinaryAdjt(str, curr+1);
}

void PrintBinaryAdj(int n)
{
    string str(n, '0');
    PrintBinaryAdjt(str, 0);
}

// more general case:
void Move(list<int>& nums, const int curr)
{
    for (list<int>::iterator itr=nums.begin(); itr!=nums.end(); ++itr)
    {
        if (*itr == curr)
        {
            itr = nums.erase(itr);
            return;
        }
    }

    nums.push_back(curr);
}

void PrintCombinationsAdj(list<int>& nums, int curr)
{
    if (curr < 0)
    {
        for (list<int>::iterator itr=nums.begin(); itr!=nums.end(); ++itr)
        {
            cout << *itr << ", ";
        }
        cout << endl;
        return;
    }

    PrintCombinationsAdj(nums, curr-1);
    Move(nums, curr);
    PrintCombinationsAdj(nums, curr-1);
}

void PrintCombinationsAdj(int n)
{
    list<int> nums;
    PrintCombinationsAdj(nums, n-1);
}

// Without restriction of adjacency:
void PrintCombinations(vector<int>& nums, int size, int curr)
{
    if (curr < 0)
    {
        for (int i=0; i<size; ++i)
        {
            cout << nums[i] << " ";
        }
        cout << endl;
        return;
    }

    PrintCombinations(nums, size, curr-1);
    nums[size] = curr;
    PrintCombinations(nums, size+1, curr-1);
}

void PrintCombinations(int n)
{
    vector<int> nums(n, -1);
    PrintCombinations(nums, 0, n-1);
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    int num = 3;

    PrintBinaryAdj(num);

    PrintCombinationsAdj(num);

    PrintCombinations(num);

    return 0;
}