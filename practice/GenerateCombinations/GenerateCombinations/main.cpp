//////////////////////////////////////////////////////////////////////////
// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
// 
//     For example,
//     If n = 4 and k = 2, a solution is:
// 
// [
//     [2,4],
//     [3,4],
//     [2,3],
//     [1,2],
//     [1,3],
//     [1,4],
// ]
//
// AllCombination(n) generates all combinations of k numbers and k from 0 to n
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > results;
        vector<int> combo(k);
        Combinations(results, combo, 0, 1, n, k);
        return results;
    }

    vector<vector<int> > AllCombinations(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > results;
        vector<int> combo;
        AllCombinations(results, combo, 0, 1, n);
        return results;
    }


private:
    void AllCombinations(vector<vector<int> >& results, vector<int>& cmb, int idx, int curr, int n)
    {
        results.push_back(cmb);
        if (curr>n) return;

        for (int num=curr; num<=n; ++num)
        {
            cmb.push_back(num);
            AllCombinations(results, cmb, idx+1, num+1, n);
            cmb.pop_back();
        }
    }

    void Combinations(vector<vector<int> >& results, vector<int>& cmb, int idx,
        int curr, int n, int k)
    {
        if(idx==k) { results.push_back(cmb); return; }

        for(int num=curr; num<=n; ++num)
        {
            cmb[idx] = num;
            Combinations(results, cmb, idx+1, num+1, n, k);
        }
    }
};

int main(int argc, char** argv)
{
    Solution solver;
    vector<vector<int> > results = solver.combine(4, 2);
    vector<vector<int> > acmbs = solver.AllCombinations(3);

    return 0;
}