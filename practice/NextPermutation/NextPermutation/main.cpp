#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    template<class T>
    void ReverseVectorPart(vector<T>& vec, int i, int j)
    {
        while (i<j)
        {
            swap(vec[i++], vec[j--]);
        }
    }

    bool nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (int i=num.size()-2; i>=0; --i)
        {
            int j = i+1;
            if (num[i] < num[j])
            {
                int k = num.size() - 1;
                while (k>i && !(num[k]>num[i])) --k;
                swap(num[i], num[k]);
                ReverseVectorPart<int>(num, j, num.size()-1);
                return true;
            }
        }

        ReverseVectorPart<int>(num, 0, num.size()-1);
        return false;
    }
};

int main(int argc, char** argv)
{
    int ary[] = { 1, 2, 3, 4 };
    vector<int> nums(ary, ary+sizeof(ary)/sizeof(ary[0]));

    Solution solver;
    do 
    {
        for (int i=0; i<nums.size(); ++i)
        {
            cout << nums[i] << "   ";
        }
        cout << endl;
    } while (solver.nextPermutation(nums));

    return 0;
}