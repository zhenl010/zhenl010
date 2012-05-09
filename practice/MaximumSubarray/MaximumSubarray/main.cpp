// Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
//     For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
//     the contiguous subarray [4,-1,2,1] has the largest sum = 6.
//////////////////////////////////////////////////////////////////////////
#include <algorithm> // where max/min defined

class Solution {
public:
    int maxSubArray(int A[], int n) { // (containing at least one number)
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int maxsum = A[0];
        int curr = A[0];
        for (int i=1; i<n; ++i)
        {
            curr = curr>0 ? curr+A[i] : A[i];
            if (maxsum < curr) maxsum = curr;
        }
        return maxsum;
    }

    int maxSubArrayRe(int A[], int n) { // (containing at least one number)
        int* B = new int[n];
        B[0] = A[0];
        for (int i=1; i<n; ++i) B[i]=B[i-1]+A[i];
        int maxsum = MaxSubRe(A, B, 0, n-1);
        delete [] B;
        return maxsum;
    }

private:
    int MaxSubRe(int* A, int* B, int lfi, int rti)
    {
        if (lfi == rti) return A[lfi];

        int cti = lfi + (rti-lfi)/2;
        int lfmin = B[lfi];
        for (int i=lfi+1; i<=cti; ++i)
        {
            if (B[i]<lfmin) lfmin = B[i];
        }
        int rtmax = B[rti];
        for (int i=cti+1; i<rti; ++i)
        {
            if (B[i]>rtmax) rtmax = B[i];
        }
        rtmax = lfmin<0 ? rtmax-lfmin : rtmax;
        int maxsum = std::max(MaxSubRe(A,B,lfi,cti),MaxSubRe(A,B,cti+1,rti));
        return std::max(maxsum, rtmax);
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    // int arry[] = { 9,0,-2,-2,-3,-4,0,1,-4,5,-8,7,-3,7,-6,-4,-7,-8 };
    int arry[] = { 1, 2 };
    
    // expect 11
    int maxsum = solver.maxSubArray(arry, sizeof(arry)/sizeof(arry[0]));
    int maxsumre = solver.maxSubArrayRe(arry, sizeof(arry)/sizeof(arry[0]));

    return 0;
}