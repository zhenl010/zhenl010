// //////////////////////////////////////////////////////////////////////////
// Jump Game
//     Given an array of non-negative integers, you are initially positioned at the first index of the array.
//     Each element in the array represents your maximum jump length at that position.
//     Determine if you are able to reach the last index.
//     For example:A = [2,3,1,1,4], return true.     A = [3,2,1,0,4], return false.
// //////////////////////////////////////////////////////////////////////////
// Jump Game II
//     Given an array of non-negative integers, you are initially positioned at the first index of the array.
//     Each element in the array represents your maximum jump length at that position.
//     Your goal is to reach the last index in the minimum number of jumps.
//     For example:
// Given array A = [2,3,1,1,4]
// The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
// //////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(int A[], int n) { // n is number of elements !
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(n<0) return false;

        int curr = 0;
        int reach = 0;
        while (curr <= reach)
        {
            reach = std::max(curr+A[curr], reach);
            if (n <= reach+1) return true;
            ++curr;
        }
        return false;
    }

    int OptimalJump(int A[], int n)
    {
        vector<int> jumps(n, INT_MAX);
        jumps[0] = 0;
        int curr = 0;
        int reach = 0;
        while (curr<n && curr<=reach)
        {
            if (curr+A[curr] > reach)
            {
                reach = curr+A[curr];
                for (int i=curr; i<n && i<=curr+A[curr]; ++i)
                {
                    jumps[i] = min(jumps[i], jumps[curr]+1);
                }
            }
            ++curr;
        }

        return jumps[n-1];
    }
};

int main(int argc, char** argv)
{
    Solution solver;
    int stps[] = { 1, 2 };
    int num = sizeof(stps) / sizeof(stps[0]);
    bool jumpable = solver.canJump(stps, num);
    int jumps = solver.OptimalJump(stps, num);

    return 0;
}