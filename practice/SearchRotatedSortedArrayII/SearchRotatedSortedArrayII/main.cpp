//////////////////////////////////////////////////////////////////////////
// Follow up for "Search in Rotated Sorted Array":
// What if duplicates are allowed?
// Would this affect the run-time complexity? How and why?
// Write a function to determine if a given target is in the array.
//////////////////////////////////////////////////////////////////////////
#include <iostream>

class Solution {
public:
    bool search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return FindIndex(A, 0, n-1, target) >= 0;
    }

    int FindIndex(int A[], int lfi, int rti, int target) {
        if (rti < lfi) return -1;
        if (lfi == rti) return A[lfi]==target ? lfi : -1;

        int cti = lfi;
        while (lfi <= rti) {
            cti = lfi + (rti-lfi)/2;
            if (A[cti] == target) {
                return cti; // found match
            }

            if (A[cti] < A[lfi]) { // right half normal
                if (target<=A[rti] && target>A[cti]) {
                    return FindIndexSorted(A, cti+1, rti, target);
                } else {
                    rti = cti-1;
                }
            } else if (A[cti] > A[lfi]) { // left half normal
                if (target>=A[lfi] && target<A[cti]) {
                    return FindIndexSorted(A, lfi, cti-1, target);
                } else {
                    lfi = cti+1;
                }
            } else { // dup found!!!
                if (A[cti] < A[rti]) { // search right half only
                    return FindIndex(A, cti+1, rti, target);
                } else { // too bad have to search both halves
                    int idx = FindIndex(A, lfi, cti-1, target);
                    if (idx < 0) {
                        return FindIndex(A, cti+1, rti, target);
                    } else {
                        return idx;
                    }
                }
            }
        }
        return -1;
    }

private:
    int FindIndexSorted(int A[], int lfi, int rti, int target) {
        int cti = lfi;
        while (lfi <= rti) {
            cti = lfi + (rti-lfi)/2;
            if (target < A[cti]) {
                rti = cti-1;
            } else if (A[cti] < target) {
                lfi = cti+1;
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

    int arry[] = { 4, 5, 6, 7, 0, 1, 2 };
    int target = 4; // 1
    bool isfound = solver.search(arry, sizeof(arry)/sizeof(int), target);

    return 0;
}