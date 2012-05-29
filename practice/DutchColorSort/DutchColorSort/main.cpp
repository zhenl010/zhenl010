//////////////////////////////////////////////////////////////////////////
// Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent,
// with the colors in the order red, white and blue.
// Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
// Note:
// You are not suppose to use the library's sort function for this problem.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

class Solution {
public:
    void sortColors(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lfi = -1;
        int rti = n;
        int idx = 0;
        while(idx<rti) {
            if(A[idx] == 0) {
                std::swap(A[++lfi], A[idx++]);
            } else if(A[idx] == 1) {
                ++idx;
            } else if(A[idx] == 2) {
                std::swap(A[idx], A[--rti]);
            } else {
                // not supposed to reach here
                throw("INPUT ERROR!");
            }
        }
    }
};

int main(int argc, char** argv)
{
    return 0;
}