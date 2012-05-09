//////////////////////////////////////////////////////////////////////////
// Given a 2D binary matrix filled with 0's and 1's, 
// find the largest rectangle containing all ones and return its area.
// passed online judge :p
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <stack>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (matrix.empty()) return 0;

        vector<int> buffer(matrix[0].size(), 0);
        int maxarea = 0;
        for (int i=0; i<(int)matrix.size(); ++i)
        {
            for (int j=0; j<(int)matrix[i].size(); ++j)
            {
                if (matrix[i][j] == '1')
                {
                    ++buffer[j];
                } 
                else
                {
                    buffer[j] = 0;
                }
            }

            maxarea = max(maxarea, MaxRectAreaHis(buffer));
        }

        return maxarea;
    }

private:
    struct RectEdge { int x; int h; };
    int MaxRectAreaHis(const vector<int>& hist);
};

int Solution::MaxRectAreaHis(const vector<int>& hist)
{
    int maxarea = 0;
    stack<RectEdge> recs;
    RectEdge sentinal = { 0, 0 };
    recs.push(sentinal);
    int histsize = hist.size();
    for(int i=0; i<histsize; ++i)
    {
        int last = i;
        while(hist[i] < recs.top().h)
        {
            maxarea = max(maxarea, recs.top().h*(i-recs.top().x));
            last = recs.top().x;
            recs.pop();
        }

        if(recs.top().h < hist[i])
        {
            RectEdge edge = { last, hist[i] };
            recs.push(edge);
        }
    }

    while(recs.empty() != true)
    {
        maxarea = max(maxarea, recs.top().h*(histsize-recs.top().x));
        recs.pop();
    }

    return maxarea;
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    vector<vector<char> > mat;

    char arry[] = "01";
    // vector<char> line(arry, arry+sizeof(arry)/sizeof(arry[0]));
    vector<char> line(arry, arry+strlen(arry));
    mat.push_back(line);

    int maxarea = solver.maximalRectangle(mat);

    return 0;
}