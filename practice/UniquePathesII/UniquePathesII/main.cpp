#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > counts(obstacleGrid.size());
        for(int i=0; i<counts.size(); ++i) {
            counts[i] = vector<int>(obstacleGrid[i].size(), 0);
        }

        // Init
        counts[0][0] = obstacleGrid[0][0]==1 ? 0 : 1;

        for(int i=1; i<counts.size(); ++i) {
            counts[i][0] = obstacleGrid[i][0]==1 ? 0 : counts[i-1][0];             
        }
        for(int j=1; j<counts[0].size(); ++j) {
            counts[0][j] = obstacleGrid[0][j]==1 ? 0 : counts[0][j-1];
        }

        // Update
        for(int i=1; i<counts.size(); ++i) {
            for(int j=1; j<counts[i].size(); ++j) {
                if(obstacleGrid[i][j]==1) {
                    counts[i][j] = 0;
                } else {
                    counts[i][j] = counts[i-1][j]+counts[i][j-1];
                }
            }
        }
        return *((*counts.rbegin()).rbegin());
    }
};

int main() {
    return 0;
}