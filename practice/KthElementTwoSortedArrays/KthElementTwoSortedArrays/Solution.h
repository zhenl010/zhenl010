// There are two sorted arrays A and B of size m and n respectively. 
// Find the kth element which can be used to find the median of the two sorted arrays. 
// The overall run time complexity should be O(log (m+n)).
//////////////////////////////////////////////////////////////////////////
#ifndef TEST_SOLUTION_H_
#define TEST_SOLUTION_H_

class Solution
{
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n);

    int KthElement(int* A, int m, int* B, int n, int k);

private:
    int KthElementNum(int* A, int m, int* B, int n, int k);
};

#endif