#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:

    int threeSumClosest(std::vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());

        int index = 0;
        int vec_size = (int)num.size();
        int distance = INT_MAX;
        int curr_sum = INT_MIN;
        while (index < vec_size)
        {
            int lf_idx = index+1;
            int rt_idx = num.size()-1;
            while ( lf_idx < rt_idx )
            {
                int curr_distance = num[index]+num[lf_idx]+num[rt_idx];
                if ( target < curr_distance )
                {
                    if (abs(curr_distance-target) < distance)
                    {
                        distance = abs(curr_distance-target);
                        curr_sum = curr_distance;
                    }

                    while (num[rt_idx-1]==num[rt_idx])
                    {
                        --rt_idx;
                    }
                    --rt_idx;
                }
                else if ( curr_distance < target )
                {
                    if (abs(curr_distance-target) < distance)
                    {
                        distance = abs(curr_distance-target);
                        curr_sum = curr_distance;
                    }

                    while (num[lf_idx+1]==num[lf_idx])
                    {
                        ++lf_idx;
                    }
                    ++lf_idx;
                }
                else // exact match !!!
                {
                    return target;
                }
            }

            while ((index+1)<vec_size && num[index+1]==num[index])
            {
                ++index;
            }
            ++index;
        }

        return curr_sum;
    }

    std::vector<int> TripletClosest(std::vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        using namespace std;

        sort(num.begin(), num.end());

        int index = 0;
        int vec_size = (int)num.size();
        int distance = INT_MAX;
        std::vector<int> results(3);
        while (index < vec_size)
        {
            int lf_idx = index+1;
            int rt_idx = num.size()-1;
            while ( lf_idx < rt_idx )
            {
                int curr_distance = num[index]+num[lf_idx]+num[rt_idx];
                if ( target < curr_distance )
                {
                    if (abs(curr_distance-target) < distance)
                    {
                        distance = abs(curr_distance-target);
                        results[0] = num[index];
                        results[1] = num[lf_idx];
                        results[2] = num[rt_idx];
                    }

                    while (num[rt_idx-1]==num[rt_idx])
                    {
                        --rt_idx;
                    }
                    --rt_idx;
                }
                else if ( curr_distance < target )
                {
                    if (abs(curr_distance-target) < distance)
                    {
                        distance = abs(curr_distance-target);
                        results[0] = num[index];
                        results[1] = num[lf_idx];
                        results[2] = num[rt_idx];
                    }

                    while (num[lf_idx+1]==num[lf_idx])
                    {
                        ++lf_idx;
                    }
                    ++lf_idx;
                }
                else // exact match !!!
                {
                    results[0] = num[index];
                    results[1] = num[lf_idx];
                    results[2] = num[rt_idx];

                    return results;
                }
            }

            while ((index+1)<vec_size && num[index+1]==num[index])
            {
                ++index;
            }
            ++index;
        }

        return results;
    }
};

int main(int argc, char* argv)
{
    int array[] = { 1,1,-1,-1,3 };
    std::vector<int> nums(array, array+sizeof(array)/sizeof(array[0]));

    int target = 3;
    Solution solver;

    int cloest_sum = solver.threeSumClosest(nums, target);

    std::vector<int> results = solver.TripletClosest(nums, target);

    return 0;
}