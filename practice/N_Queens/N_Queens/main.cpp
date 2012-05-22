#include <iostream>
#include <string>
#include <vector>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string> > results;
        vector<int> places(n);
        SolveNQueensRe(results, places, 0, n);
        return results;
    }

private:
    void SolveNQueensRe(vector<vector<string> >& results, vector<int>& places, int idx, int n) {
        if(idx==n) {
            AddConfiguration(results, places, n);
            return;
        }

        for(int j=0; j<n; ++j) {
            if(IsValid(j, places, idx)) {
                places[idx] = j;
                SolveNQueensRe(results, places, idx+1, n);
            }
        }
    }

    void AddConfiguration(vector<vector<string> >& results, vector<int>& places, int n) {
        vector<string> conf;
        for(int i=0; i<n; ++i) {
            string line(n, '.');
            line[places[i]] = 'Q';
            conf.push_back(line);
        }
        results.push_back(conf);
    }

public:
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int number = 0;
        vector<int> recs(n);
        NQueenNums(number, recs, 0, n);
        return number;
    }

private:
    bool IsValid(int col, vector<int>& recs, int idx)
    {
        for (int i=0; i<idx; ++i)
        {
            if (col==recs[i] || col-recs[i]==i-idx || col-recs[i]==idx-i)
            {
                return false;
            }
        }
        return true;
    }

    void NQueenNums(int& num, vector<int>& recs, int idx, int n) {
        if(idx==n) {
            ++num;
            return;
        }

        for(int j=0; j<n; ++j) {
            if(IsValid(j, recs, idx)) {
                recs[idx] = j;
                NQueenNums(num, recs, idx+1, n);
            }
        }
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    vector<vector<string> > results = solver.solveNQueens(4);

    for (int i=4; i<26; ++i)
    {
        int num = solver.totalNQueens(i);
        cout << i << "      " << num << endl;
    }

    return 0;
}