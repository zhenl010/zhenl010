//////////////////////////////////////////////////////////////////////////
// Given a set of distinct integers, S, return all possible subsets.
// Note:
// Elements in a subset must be in non-descending order.
// The solution set must not contain duplicate subsets.
// For example,
// If S = [1,2,3], a solution is:
// [
// [3],
// [1],
// [2],
// [1,2,3],
// [1,3],
// [2,3],
// [1,2],
// []
// ]
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Assume set represented by vector and no duplicate 
//////////////////////////////////////////////////////////////////////////
template <typename T>
void GenerateSubsets(vector<vector<T> >& subsets, vector<T>& recs, int curr, int n, int k) {
    vector<T> cmb(curr);
    for (int i=0; i<curr; ++i) { cmb[i] = recs[i]; }
    subsets.push_back(cmb);

    for(int i=k; i<n; ++i) {
        swap(recs[curr], recs[i]);
        GenerateSubsets<T>(subsets, recs, curr+1, n, i+1);
        swap(recs[curr], recs[i]);
    }
}

//////////////////////////////////////////////////////////////////////////
// Assume set represented by vector, no duplicate, sorted
//////////////////////////////////////////////////////////////////////////
template <typename T>
vector<vector<T> > AllSubSets(vector<T>& recs) {
    // sort(recs.begin(), recs.end()); // assume
    vector<vector<T> > subsets;
    GenerateSubsets(subsets, recs, 0, recs.size(), 0);
    return subsets;
}

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(S.begin(), S.end());
        return AllSubSets<int>(S);
    }
};

int main(int argc, char** argv)
{
    Solution solver;
    int arry[] = { 1, 2 };
    vector<int> nums(arry, arry+sizeof(arry)/sizeof(int));
    vector<vector<int> > subsets = solver.subsets(nums);

    return 0;
}