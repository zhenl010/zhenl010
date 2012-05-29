#include <iostream>

class Solution {
public:
    //////////////////////////////////////////////////////////////////////////
    // Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
    // Do not allocate extra space for another array, you must do this in place with constant memory.
    // For example,
    // Given input array A = [1,1,2],
    // Your function should return length = 2, and A is now [1,2].
    //////////////////////////////////////////////////////////////////////////
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(n<=1) return n;

        int prev = A[0];
        int length = 1;
        for(int i=1; i<n; ++i) {
            if(A[i]!=prev) {
                prev = A[i];
                A[length++] = prev;
            }
        }
        return length;
    }

    //////////////////////////////////////////////////////////////////////////
    // Follow up for "Remove Duplicates":
    // What if duplicates are allowed at most twice?
    // 
    // For example,
    // Given sorted array A = [1,1,1,2,2,3],
    // 
    // Your function should return length = 5, and A is now [1,1,2,2,3].
    //////////////////////////////////////////////////////////////////////////
    int RemoveDuplicatesTwo(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(n<=2) return n;

        int prev = A[0];
        int count = 1;
        int length = 1;
        for(int i=1; i<n; ++i) {
            if(A[i] != prev) {
                prev = A[i];
                count = 1;
                A[length++] = prev;
            } else if(count<2) {
                ++count;
                A[length++] = prev;
            }
        }

        return length;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    return 0;
}