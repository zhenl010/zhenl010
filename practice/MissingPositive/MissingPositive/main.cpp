#include <iostream>

class Solution {
public:
    int firstMissingPositive(int arry[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for(int i=0; i<n; ++i)
        {
            int idx = arry[i]-1;
            while (arry[i] != i+1 && 0<=idx && idx<n && arry[i]!=arry[idx])
            {
                std::swap(arry[i], arry[idx]);
                idx = arry[i]-1;
            }
        }

        for(int i=0; i<n; ++i)
        {
            if(arry[i] != i+1) return i+1;
        }

        return n+1;
    }
};

int main(int argc, char** argv)
{
    int nums[] = { 1, 1, -3, 2, 4 };

    Solution solver;
    int missing = solver.firstMissingPositive(nums, sizeof(nums)/sizeof(nums[0]));

    return 0;
}