//////////////////////////////////////////////////////////////////////////
// Given a sorted array and a target value, return the index if the target is found. 
// If not, return the index where it would be if it were inserted in order.
// You may assume no duplicates in the array.
// 
// Here are few examples.
// [1,3,5,6], 5 → 2
// [1,3,5,6], 2 → 1
// [1,3,5,6], 7 → 4
// [1,3,5,6], 0 → 0
//////////////////////////////////////////////////////////////////////////
#include <iostream>

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lfi = 0;
        int rti = n-1;
        int cti = lfi;
        while(lfi <= rti) {
            cti = lfi + (rti-lfi)/2;
            if(target < A[cti]) {
                if(target < A[lfi]) return lfi;
                rti = cti-1;
            } else if(A[cti] < target) {
                if(A[rti] < target) return rti+1;
                lfi = cti+1;
            } else {
                return cti;
            }
        }
        // should never reach here
    }
};

int main(int argc, char** argv)
{
    return 0;
}