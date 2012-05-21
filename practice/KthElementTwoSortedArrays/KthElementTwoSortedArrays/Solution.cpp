#include "Solution.h"
#include <cassert>

double Solution::findMedianSortedArrays(int A[], int m, int B[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if ((m+n)%2==1) {
        return KthElement(A, m, B, n, (m+n)/2+1);
    } else {
        return 0.5*(KthElement(A, m, B, n, (m+n)/2)+KthElement(A, m, B, n, (m+n)/2+1));
    }
}

int Solution::KthElement(int* A, int m, int* B, int n, int k) {
    if (n<m) return KthElement(B, n, A, m, k); // optional optimization?
    assert(0<k && k<=m+n);
    int na = KthElementNum(A, m, B, n, k);
    if (na == 0) return B[k-1];
    if (na == k) return A[k-1];
    return A[na-1] > B[k-na-1] ? A[na-1] : B[k-na-1];
}

int Solution::KthElementNum(int* A, int m, int* B, int n, int k) {
    if (n==0) return k;

    bool found = false;
    int lfa = 0;
    int rta = k<m ? k : m;
    int cta = lfa + (rta-lfa)/2;
    while (lfa<=rta && found!=true) {
        cta = lfa + (rta-lfa)/2;
        int nb = k-cta;
        if (nb>n || A[cta]<B[k-cta-1]) {
            lfa = cta+1;
        } else if (nb<n && B[nb]<A[cta-1]) {
            rta = cta-1;
        } else {
            return cta;
        }
    }
    return cta;
}