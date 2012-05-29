//////////////////////////////////////////////////////////////////////////
// Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
// For example,
// Given the following matrix:
// [
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
// ]
// You should return [1,2,3,6,9,8,7,4,5].
//////////////////////////////////////////////////////////////////////////
// Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
// For example,
// Given n = 3,
// You should return the following matrix:
// [
// [ 1, 2, 3 ],
// [ 8, 9, 4 ],
// [ 7, 6, 5 ]
// ]
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> nums;
        if(matrix.empty() || (*matrix.begin()).empty()) return nums;

        int rowmin = 0;
        int rowmax = matrix.size()-1;
        int colmin = 0;
        int colmax = (*matrix.begin()).size()-1;
        nums.resize(matrix.size() * (*matrix.begin()).size());
        int idx = 0;
        while(rowmin<=rowmax && colmin<=colmax) {
            for(int col=colmin; col<=colmax; ++col) {
                nums[idx++] = matrix[rowmin][col];                
            }
            ++rowmin;
            if(rowmax<rowmin) continue;
            for(int row=rowmin; row<=rowmax; ++row) {
                nums[idx++] = matrix[row][colmax];
            }
            --colmax;
            if(colmax<colmin) continue;
            for(int col=colmax; col>=colmin; --col) {
                nums[idx++] = matrix[rowmax][col];
            }
            --rowmax;
            for(int row=rowmax; row>=rowmin; --row) {
                nums[idx++] = matrix[row][colmin];
            }
            ++colmin;
        }
        return nums;
    }

    vector<vector<int> > generateMatrix(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > matrix;
        if(n<=0) return matrix;

        int rowmin = 0;
        int rowmax = n-1;
        int colmin = 0;
        int colmax = n-1;
        int num = 0;
        matrix.resize(n);
        for(int i=0; i<n; ++i) matrix[i].resize(n);
        while(rowmin<=rowmax && colmin<=colmax) {
            for(int col=colmin; col<=colmax; ++col) {
                matrix[rowmin][col] = ++num;
            }
            ++rowmin;
            if(rowmax<rowmin) continue;
            for(int row=rowmin; row<=rowmax; ++row) {
                matrix[row][colmax] = ++num;
            }
            --colmax;
            if(colmax<colmin) continue;
            for(int col=colmax; col>=colmin; --col) {
                matrix[rowmax][col] = ++num;
            }
            --rowmax;
            for(int row=rowmax; row>=rowmin; --row) {
                matrix[row][colmin] = ++num;
            }
            ++colmin;
        }        
        return matrix;
    }
};

int main(int argc, char** argv)
{
    return 0;
}