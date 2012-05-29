//////////////////////////////////////////////////////////////////////////
// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
// You are given a target value to search. If found in the array return its index, otherwise return -1.
// You may assume no duplicate exists in the array.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

class Solution {
public:
    int search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(n<1) return -1;

        if(target<A[0]) {
            return BinarySearch(A, PivotIndex(A, n)+1, n-1, target);
        } else {
            return BinarySearch(A, 0, PivotIndex(A, n), target);
        }
    }

private:
    int PivotIndex(int A[], int n) {
        int head = A[0];
        int lfi = 0;
        int rti = n-1;
        while(lfi<rti) {
            int cti = rti-(rti-lfi)/2;
            if(A[cti]<head) {
                rti = cti-1;
            } else {
                lfi = cti;
            }
        }
        return rti;
    }

    int BinarySearch(int A[], int lfi, int rti, int target) {
        int cti = rti; // precondition assert rti always valid
        while(lfi <= rti) {
            cti = lfi + (rti-lfi)/2;
            if(A[cti] < target) {
                lfi = cti+1;
            } else if(A[cti] > target) {
                rti = cti-1;
            } else { // found
                return cti;
            }
        }
        return -1;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    int arry[] = { 4,5,6,7,0,1,2 };
    int target = 4; // 1
    int idx = solver.search(arry, sizeof(arry)/sizeof(int), target);

    return 0;
}