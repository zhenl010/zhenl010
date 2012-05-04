//////////////////////////////////////////////////////////////////////////
// Write a function to find the longest common prefix string amongst an array of strings.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string lcpx;
        if(strs.empty()) return lcpx;

        lcpx = strs[0];
        for(int i=0; i<strs.size(); ++i)
        {
            string last = lcpx;
            lcpx.clear();
            for(int j=0; j<last.size() && j<strs[i].size() && last[j]==strs[i][j]; ++j)
            {
                lcpx += last[j];
            }
        }
        return lcpx;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    vector<string> strs;
    strs.push_back("a");

    string lcpx = solver.longestCommonPrefix(strs);

    return 0;
}