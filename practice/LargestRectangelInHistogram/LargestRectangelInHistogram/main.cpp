// Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
//     find the area of largest rectangle in the histogram.
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    struct RectEdge
    {
        int x;
        int height;
    };

    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(height.empty()) return 0;

        int maxarea = 0;
        int idx = 0;
        stack<RectEdge> recs;
        while(idx < height.size())
        {
            RectEdge edge = { idx, height[idx] };
            while(recs.empty()!=true && edge.height<recs.top().height)
            {
                maxarea = max(maxarea, (idx-recs.top().x)*recs.top().height);
                edge.x = recs.top().x;
                recs.pop();
            }
            if (recs.empty()==true || recs.top().height<edge.height)
            {
                recs.push(edge);
            } 
            ++idx;
        }

        while(recs.empty()!=true)
        {
            maxarea = max(maxarea, (idx-recs.top().x)*recs.top().height);
            recs.pop();
        }

        return maxarea;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    const int arry[] = {4, 2, 3};
    vector<int> hts(arry, arry+sizeof(arry)/sizeof(arry[0]));

    int area = solver.largestRectangleArea(hts);
    
    return 0;
}