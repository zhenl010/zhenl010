// Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right
// which minimizes the sum of all numbers along its path.
// Note: You can only move either down or right at any point in time.
#include <vector>

namespace
{
//////////////////////////////////////////////////////////////////////////
    
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(grid.empty() || grid.begin()->empty()) return 0;
        vector<int> sums(grid.begin()->size(),0);
        sums[0] = grid[0][0];
        for(int j=1; j<sums.size(); ++j) {
            sums[j] = sums[j-1] + grid[0][j];
        }

        for(int i=1; i<grid.size(); ++i) {
            sums[0] = sums[0] + grid[i][0];
            for(int j=1; j<sums.size(); ++j) {
                sums[j]=min(sums[j], sums[j-1])+grid[i][j];
            }
        }

        return *sums.rbegin();
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    const int rownum = 3;
    const int colnum = 3;
    int arrys[rownum][colnum] = { {1,3,1}, {1,5,1}, {4,2,1} };
    vector<vector<int> > grid(rownum);
    for (int i=0; i<rownum; ++i)
    {
        grid[i] = vector<int>(arrys[i], arrys[i]+colnum);
    }

    Solution solver;
    int result = solver.minPathSum(grid);

    return 0;
}