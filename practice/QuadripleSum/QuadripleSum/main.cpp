#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector< std::vector<int> > QuadripletSum(std::vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        using namespace std;

        std::vector< std::vector<int> > results;

        sort(num.begin(), num.end());

        int vec_size = (int)num.size();
        int lf_outer = 0;
        std::vector<int> quadriplet(4,0);
        while (lf_outer < vec_size)
        {
            int rt_outer = vec_size - 1;
            while (lf_outer+2 < rt_outer)
            {
                int out_sum = num[lf_outer] + num[rt_outer];
                int lf_idx = lf_outer+1;
                int rt_idx = rt_outer-1;
                while ( lf_idx < rt_idx )
                {
                    int curr_sum = num[lf_idx]+num[rt_idx] + out_sum;
                    if ( target < curr_sum )
                    {
                        while (num[rt_idx-1]==num[rt_idx])
                        {
                            --rt_idx;
                        }
                        --rt_idx;
                    }
                    else if ( curr_sum < target )
                    {
                        while (num[lf_idx+1]==num[lf_idx])
                        {
                            ++lf_idx;
                        }
                        ++lf_idx;
                    }
                    else // exact match !!!
                    {
                        quadriplet[0] = num[lf_outer];
                        quadriplet[1] = num[lf_idx];
                        quadriplet[2] = num[rt_idx];
                        quadriplet[3] = num[rt_outer];
                        results.push_back(quadriplet);

                        while (num[rt_idx-1]==num[rt_idx])
                        {
                            --rt_idx;
                        }
                        --rt_idx;

                        while (num[lf_idx+1]==num[lf_idx])
                        {
                            ++lf_idx;
                        }
                        ++lf_idx;
                    }
                }

                while ((rt_outer-1)>=0 && num[rt_outer-1]==num[rt_outer])
                {
                    --rt_outer;
                }
                --rt_outer;
            }
            
            while ((lf_outer+1)<vec_size && num[lf_outer+1]==num[lf_outer])
            {
                ++lf_outer;
            }
            ++lf_outer;
        }

        return results;
    }
};

int main(int argc, char* argv)
{
    int array[] = { 1,1,-1,-1,2,3,-2,0,0,0,0 };
    std::vector<int> nums(array, array+sizeof(array)/sizeof(array[0]));

    int target = 4;
    Solution solver;
    std::vector< std::vector<int> > results = solver.QuadripletSum(nums, target);

    return 0;
}