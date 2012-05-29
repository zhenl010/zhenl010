//////////////////////////////////////////////////////////////////////////
// Given a collection of numbers that might contain duplicates, return all 
// possible unique permutations.
// 
// For example,
// [1,1,2] have the following unique permutations:
// [1,1,2], [1,2,1], and [2,1,1].
// 
// 注意{ -1,2,0,-1,1,0,1 }有630个不同的permutations
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct ItmCount
    {
        int val;
        int count;
    };

    vector<ItmCount> CountUniqueItems(vector<int> &nums)
    {
        vector<ItmCount> items;
        if (nums.empty()) return items;

        sort(nums.begin(), nums.end());
        ItmCount itm = { nums[0], 1 };
        for (int i=1; i<nums.size(); ++i) {
            if (nums[i] == nums[i-1]) {
                ++itm.count;
            } else {
                items.push_back(itm);
                itm.val = nums[i];
                itm.count = 1;
            }
        }
        items.push_back(itm);
        return items;
    }

    void GeneratePermutation(vector<vector<int> >& results, vector<int>& numbers, int idx, vector<ItmCount>& items)
    {
        if (idx == numbers.size()) {
            results.push_back(numbers);
            return;
        }

        for (int i=0; i<items.size(); ++i) {
            if (items[i].count > 0) {
                numbers[idx] = items[i].val;
                --items[i].count;
                GeneratePermutation(results, numbers, idx+1, items);
                ++items[i].count;
            }
        }
    }

public:
    //////////////////////////////////////////////////////////////////////////
    // Most efficient?
    //////////////////////////////////////////////////////////////////////////
    vector<vector<int> > UniquePermutations(vector<int> &nums)
    {
        vector<vector<int> > results;
        vector<ItmCount> items = CountUniqueItems(nums);
        GeneratePermutation(results, nums, 0, items);
        return results;
    }

    //////////////////////////////////////////////////////////////////////////
    // ihasleetcode's post saves indices that's already swaped
    //////////////////////////////////////////////////////////////////////////
    vector<vector<int> > permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        vector<vector<int> > ret;
        int n = num.size();
        bool *used = new bool[n];
        int *index = new int[n];
        memset(used, 0, n*sizeof(bool));
        permuteUnique(num, used, index, 0, ret);
        delete[] used;
        delete[] index;
        return ret;
    }

    void permuteUnique(vector<int> &num, bool used[], int index[], 
        int pos, vector<vector<int> > &ret) {
            int n = num.size();
            if (pos == n) {
                vector<int> ans;
                for (int i = 0; i < n; i++) {
                    ans.push_back(num[index[i]]);
                }
                ret.push_back(ans);
                return;
            }
            for (int i = 0; i < n; ) {
                if (used[i]) { i++; continue; }
                used[i] = true;
                index[pos] = i;
                permuteUnique(num, used, index, pos+1, ret);
                used[i] = false;
                int j = i;
                while (i < n && num[i] == num[j]) i++;
            }
    }

    //////////////////////////////////////////////////////////////////////////
    // when there's no duplicate elements:
    //////////////////////////////////////////////////////////////////////////
    vector<vector<int> > permute(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > results;
        Permute(results, 0, num);
        return results;
    }

    void Permute(vector<vector<int> >& results, int curr, vector<int>& nums)
    {
        if(curr == nums.size()-1)
        {
            results.push_back(nums);
            return;
        }

        Permute(results, curr+1, nums);
        for(int idx=curr+1; idx<nums.size(); ++idx)
        {
            swap(nums[curr], nums[idx]);
            Permute(results, curr+1, nums);
            swap(nums[curr], nums[idx]);
        }
    }
};

int main(int argc, char** argv)
{
    int arrayin[] = { -1,2,0,-1,1,0,1 };
    // int arrayin[] = { 1,1,2 };
    vector<int> nums(arrayin, arrayin+sizeof(arrayin)/sizeof(arrayin[0]));

    Solution solver;
    vector<vector<int> > ansvecs = solver.UniquePermutations(nums);
    vector<vector<int> > results = solver.permuteUnique(nums);

    set<vector<int> > verify;
    for (int i=0; i<results.size(); ++i)
    {
        int sizebefore = verify.size();
        verify.insert(results[i]);
        if (verify.size() == sizebefore)
        {
            vector<int> dupa = results[i];
            bool dupfound = true;
        }
    }

    return 0;
}