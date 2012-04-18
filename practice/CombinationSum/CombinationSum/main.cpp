#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Solution {
public:

    //////////////////////////////////////////////////////////////////////////
    // assume no duplicates in candidates
    //////////////////////////////////////////////////////////////////////////
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        typedef vector< vector<int> > Combo;
        vector<Combo> sums(target+1);
        vector<int> nums = candidates;
        sort(nums.begin(), nums.end());

        for (int i=0; i<nums.size() && nums[i]<=target; ++i)
        {
            int num = nums[i];
            vector<Combo> prevs = sums; // use clone
            vector<int> xcurr;
            int incr = 0;
            for (int j=1; j<=target/num; ++j)
            {
                incr += num;
                xcurr.push_back(num);
                sums[incr].push_back(xcurr);

                for (int k=1; k<=(target-incr); ++k)
                {
                    if (prevs[k].empty()!=true)
                    {
                        for (int idx=0; idx<prevs[k].size(); ++idx)
                        {
                            vector<int> cmb = prevs[k][idx];
                            cmb.insert(cmb.end(), xcurr.begin(), xcurr.end());
                            sums[k+incr].push_back(cmb);
                        }
                    }
                }
            }
        }

        return sums[target];
    }

    //////////////////////////////////////////////////////////////////////////
    // assume no duplicates in candidates
    //////////////////////////////////////////////////////////////////////////
    typedef vector< vector<int> > Combo;
    void SolveComboSum(Combo& results, int sum, list<int>& indices, const vector<int>& nums, int target)
    {
        if (sum > target) return;

        if (sum == target)
        {
            vector<int> cmb;
            for (list<int>::iterator itr=indices.begin(); itr!=indices.end(); ++itr)
            {
                cmb.push_back(nums[*itr]);
            }
            results.push_back(cmb);
        }

        for (int idx=indices.empty() ? 0 : (*(indices.rbegin())); idx<nums.size(); ++idx)
        {
            indices.push_back(idx);
            SolveComboSum(results, sum+nums[idx], indices, nums, target);
            indices.pop_back();
        }
    }

    Combo FindCombinationSums(vector<int> &candidates, int target) 
    {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(candidates.begin(), candidates.end());
        Combo results;
        int sum = 0;
        list<int> indices;
        SolveComboSum(results, sum, indices, candidates, target);
        return results;
    }

};

int main(int argc, char** argv)
{
    Solution solver;

    int nums[] = { 2, 3, 6, 7 };
    vector<int> candis(nums, nums+sizeof(nums)/sizeof(nums[0]));
    int target = 7;

    vector<vector<int> > result = solver.combinationSum(candis, target);
    vector<vector<int> > combos = solver.FindCombinationSums(candis, target);

    return 0;
}