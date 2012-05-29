#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> range(2, -1);

        int lfi = 0;
        int rti = n-1;
        int cti = 0;
        while(lfi<=rti) {
            cti = lfi + (rti-lfi)/2;
            if(A[cti] < target) {
                lfi = cti+1;
            } else if (A[cti] > target) {
                rti = cti-1;
            } else { // equals 
                range[0] = LeftEdgeIndex(A, lfi, cti, target);
                range[1] = RightEdgeIndex(A, cti, rti, target);
                return range;
            }
        }
        return range;
    }

private:
    int LeftEdgeIndex(int A[], int lfi, int idx, int target) {
        while(lfi<idx && A[lfi]!=target) {
            int mid = lfi + (idx-lfi)/2;
            if(A[mid] == target) {
                idx = mid;
            } else {
                lfi = mid+1;
            }
        }
        return lfi;
    }

    int RightEdgeIndex(int A[], int idx, int rti, int target) {
        while(rti>idx && A[rti]!=target) {
            int mid = rti - (rti-idx)/2; // Notice the difference here!!!
            if(A[mid] == target) {
                idx = mid;
            } else {
                rti = mid-1;
            }
        }
        return rti;        
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    int arry[] = { 7, 8, 8, 10 };
    int target =  8;

    vector<int> range = solver.searchRange(arry, sizeof(arry)/sizeof(int), target);

    return 0;
}