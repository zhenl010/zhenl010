//////////////////////////////////////////////////////////////////////////
// Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.
// For example,
// Consider the following matrix:
// [
// [1,   3,  5,  7],
// [10, 11, 16, 20],
// [23, 30, 34, 50]
// ]
// Given target = 3, return true.
//////////////////////////////////////////////////////////////////////////
// Young tableau
// An m by n Young tableau is an m by n matrix such that the entries of each row are in sorted order
// from left to right and the entries of each column are in sorted order from top to bottom. Some of the
// entries of a Young tableau may be infinity, which we treat as nonexistent elements. Thus a Young tableau
// can be used to hold r < m*n numbers.
// http://lyle.smu.edu/~saad/courses/cse3358/ps5/problemset5sol.pdf
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int row = matrix.size()-1;
        int col = 0;
        bool isdone = false;
        while(!isdone) {
            if(matrix[row][col] < target) {
                if(col+1 < matrix[row].size()) {
                    ++col;
                } else {
                    isdone = true;
                }
            } else if(matrix[row][col] > target) {
                if(row-1 >= 0) {
                    --row;
                } else {
                    isdone = true;
                }
            } else {
                isdone = true;
            }            
        }
        return matrix[row][col] == target;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    return 0;
}