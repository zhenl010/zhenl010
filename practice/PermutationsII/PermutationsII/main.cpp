#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > results;
        sort(num.begin(), num.end());

        vector<int> indices(num.size());
        for(int i=0; i<num.size(); ++i) indices[i] = i;
        PermuteUnique(results, indices, 0, num);
        return results;
    }

    void PermuteUnique(vector<vector<int> >& results, vector<int>& indices, int curr, const vector<int>& nums)
    {
        if(curr >= nums.size()) return;
        if(curr == nums.size()-1)
        {
            vector<int> answ;
            for(int i=0; i<indices.size(); ++i) answ.push_back(nums[indices[i]]);
            results.push_back(answ);
            return;
        }

        PermuteUnique(results, indices, curr+1, nums);
        int next = curr + 1;
        while (next<nums.size())
        {
            if(nums[indices[next]]!=nums[indices[curr]])
            {
                swap(indices[curr], indices[next]);
                PermuteUnique(results, indices, curr+1, nums);
                swap(indices[curr], indices[next]);
                while (next+1<nums.size() && nums[indices[next+1]]==nums[indices[next]])
                {
                    ++next;
                }            
                ++next;
            }
            else
            {
                while (next<nums.size() && nums[indices[next]]==nums[indices[curr]])
                {
                    ++next;
                }            
            }
        }
    }
};

int main(int argc, char** argv)
{
    int arrayin[] = { -1,2,0,-1,1,0,1 };
    vector<int> nums(arrayin, arrayin+sizeof(arrayin)/sizeof(arrayin[0]));

    Solution solver;
    vector<vector<int> > results = solver.permuteUnique(nums);

    return 0;
}