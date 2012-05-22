//////////////////////////////////////////////////////////////////////////
// Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
// If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
// The replacement must be in-place, do not allocate extra memory.
// Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
// 1,2,3 → 1,3,2
// 3,2,1 → 1,2,3
// 1,1,5 → 1,5,1
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
void ReverseVectorPart(vector<T>& vec, int lfi, int rti)
{
    while (lfi<rti)
    {
        swap(vec[lfi++], vec[rti--]);
    }
}

class Solution {
public:
    void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int numsize = num.size();
        for(int i=numsize-2; i>=0; --i) {
            if(num[i] < num[i+1]) {
                int rti = i+1;
                while (rti+1<numsize && num[rti+1]>num[i]) { ++rti; }
                swap(num[i], num[rti]);
                ReverseVectorPart<int>(num, i+1, numsize-1);
                return;
            }
        }
        ReverseVectorPart<int>(num, 0, numsize-1);
    }
};

int main(int argc, char** argv)
{
    int ary[] = { 1, 3, 2 };
    vector<int> nums(ary, ary+sizeof(ary)/sizeof(ary[0]));

    Solution solver;

    for (int i=0; i<2; ++i)
    {
        for (int i=0; i<nums.size(); ++i)
        {
            cout << nums[i] << "-";
        }
        cout << endl;
        solver.nextPermutation(nums);
    }

    //////////////////////////////////////////////////////////////////////////
    // compare with std::next_permutation
    //////////////////////////////////////////////////////////////////////////
    string str("1322");
    // sort(str.begin(), str.end());
    do {
        cout << str << endl;
    } while (next_permutation(str.begin(), str.end()));
    
    return 0;
}