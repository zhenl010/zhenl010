//////////////////////////////////////////////////////////////////////////
// Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
// Follow up:
// Did you use extra space?
// A straight forward solution using O(m*n) space is probably a bad idea.
// A simple improvement uses O(m + n) space, but still not the best solution.
// Could you devise a constant space solution?
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(matrix.empty() || (*matrix.begin()).empty()) return;

        int rownum = matrix.size();
        int colnum = (*matrix.begin()).size();

        bool rowhaszero = false;
        for(int j=0; !rowhaszero && j<colnum; ++j) {
            if(matrix[0][j]==0) rowhaszero = true;
        }

        bool colhaszero = false;
        for(int i=0; !colhaszero && i<rownum; ++i) {
            if(matrix[i][0]==0) colhaszero = true;
        }

        for(int i=1; i<rownum; ++i) {
            for(int j=1; j<colnum; ++j) {
                if(matrix[i][j]==0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for(int i=1; i<rownum; ++i) {
            for(int j=1; j<colnum; ++j) {
                if(matrix[i][0]==0 || matrix[0][j]==0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if(rowhaszero) {
            for(int j=0; j<colnum; ++j) matrix[0][j]=0;
        }
        if(colhaszero) {
            for(int i=0; i<rownum; ++i) matrix[i][0]=0;
        }

    }
};

int main(int argc, char** argv)
{
    return 0;
}