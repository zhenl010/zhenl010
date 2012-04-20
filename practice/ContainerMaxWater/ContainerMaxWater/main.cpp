#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int maxarea = 0;
        int lf = 0;
        int rt = height.size()-1;
        while(lf < rt)
        {
            if(height[lf] < height[rt])
            {
                int area = (rt-lf)*height[lf];
                if(area > maxarea) maxarea = area;
                while((lf+1)<rt && height[lf+1]<=height[lf]) ++lf;
                ++lf;
            }
            else if(height[rt] < height[lf])
            {
                int area = (rt-lf)*height[rt];
                if(area > maxarea) maxarea = area;
                while(rt-1>lf && height[rt-1]<=height[rt]) --rt;
                --rt;
            }
            else
            {
                int area = (rt-lf)*height[lf];
                if(area > maxarea) maxarea = area;
                ++lf;
                --rt;
            }
        }
        return maxarea;        
    }
};

int main(int argc, char** argv)
{
    int hts[] = { 2, 3, 9, 5, 7, 11, 9 };
    vector<int> heights(hts, hts+sizeof(hts)/sizeof(int));
    Solution solver;
    int maxarea = solver.maxArea(heights);

    return 0;
}