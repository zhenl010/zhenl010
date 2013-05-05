#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template<typename T, int N>
int ArraySize(T (&) [N]) { return N; }

class Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if ((m+n) % 2 == 0) {
            pair<int, int> mids = findMids(A, m, B, n);
            return (mids.first + mids.second) * 0.5;
        } else {
            return findKthElement((m+n)/2+1, A, m, B, n);
        }
    }

private:
    // Assume k,m,n non-negative and 0<k<=(m+n)
    int findKthElement(int k, int A[], int m, int B[], int n) {
        if (n==0) return A[k-1];

        // binary search
        int l = n<k ? k-n-1 : 0;
        int r = k<m ? k-1 : m-1;
        while (l<=r) {
            int i = l + ((r-l) / 2);
            int j = k - (i+2);           
            if (j<0) { // this happens when i = k-1
                if (A[i] <= B[0]) return A[i];
                r = l - 1;
            } else if (n<j+1) {
                l=i+1;
            } else if (A[i]<B[j]) {
                l = i + 1;
            } else if (j+1<n && B[j+1]<A[i]) {
                r = i - 1;
            } else {
                return A[i];
            }
        }

        return findKthElement(k, B, n, A, m);
    }

    pair<int, int> findMids(int A[], int m, int B[], int n) {
        pair<int, int> mids;
        int k = (m+n) / 2;
        mids.first = findKthElement(k, A, m, B, n);
        mids.second = findKthElement(k+1, A, m, B, n);
        return mids;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    int arr_one[] = {
        1
        // 100000
        // 1, 1
        // 1, 1, 3, 3
        // 3
        // 1, 5
        // 1, 2, 4
        // 1,4
    };

    int arr_two[] = {
        // 1
        // 100001
        // 1, 1
        // 1, 2
        // 1, 1, 3, 3
        // 2, 3
        // 2, 3, 4
        // 1, 2, 4
        // 2, 3, 4, 6
        // 3, 5, 6
        // 2,3,5,6
        2,3,4,5,6,7
    };

    double median = solver.findMedianSortedArrays(arr_one, ArraySize(arr_one), arr_two, ArraySize(arr_two));

    return 0;
}