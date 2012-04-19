//////////////////////////////////////////////////////////////////////////
// Given a collection of candidate numbers (C) and a target number (T),
// find all unique combinations in C where the candidate numbers sums to T.
// Each number in C may only be used once in the combination.
// 
// Note:
// All numbers (including target) will be positive integers.
// Elements in a combination (a1, a2, … ,ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
// The solution set must not contain duplicate combinations.
// For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
// A solution set is: 
// [1, 7] 
// [1, 2, 5] 
// [2, 6] 
// [1, 1, 6] 
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Solution {
public:
    struct ItemCount
    {
        int x;
        int count;
    };

    vector<ItemCount> CountItems(vector<int>& nums)
    {
        vector<ItemCount> items;
        if (nums.empty()) return items;

        sort(nums.begin(), nums.end());
        ItemCount itm = { nums[0], 1 };
        for (int i=1; i<nums.size(); ++i)
        {
            if (nums[i]==nums[i-1])
            {
                ++itm.count;
            } 
            else
            {
                items.push_back(itm);
                itm.x = nums[i];
                itm.count = 1;
            }
        }
        items.push_back(itm);
        return items;
    }

    void AddToResult(vector<vector<int> >& results, list<ItemCount>& cmb)
    {
        vector<int> answ;
        for (list<ItemCount>::iterator itr=cmb.begin(); itr!=cmb.end(); ++itr)
        {
            vector<int> part((*itr).count, (*itr).x);
            answ.insert(answ.end(), part.begin(), part.end());
        }
        results.push_back(answ);
    }

    void ComboSumII(vector<vector<int> >& results, list<ItemCount>& cmb,
        vector<ItemCount>& items, int target, int curr)
    {
        if(target==0) { AddToResult(results, cmb); return; }
        if(curr==items.size() || target<0) return;

        for(int i=curr; i<items.size(); ++i)
        {
            for (int cnt=1; cnt<=items[i].count; ++cnt)
            {
                ItemCount itm = { items[i].x, cnt };
                cmb.push_back(itm);
                ComboSumII(results, cmb, items, target-cnt*itm.x, i+1);
                cmb.pop_back();
            }
        }
    }

    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > results;
        vector<ItemCount> items = CountItems(num);
        list<ItemCount> combo;
        ComboSumII(results, combo, items, target, 0);
        return results;
    }
};

int main(int argc, char** argv)
{
    int ary[] = { 1, 2 };
    vector<int> nums(ary, ary+sizeof(ary)/sizeof(int));

    Solution solver;
    int target = 2;
    vector<vector<int> > results = solver.combinationSum2(nums, target);

    return 0;
}