#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int> > TripsSumToZero(std::vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        using namespace std;

        sort(num.begin(), num.end());

        vector< vector<int> > results;
        vector<int> triplet(3, INT_MIN);
        int tar_idx = 0;
        int vec_size = (int)num.size();
        while (tar_idx < vec_size)
        {
            int attemp_sum = -num[tar_idx];
            int lf_idx = tar_idx+1;
            int rt_idx = num.size()-1;
            while ( lf_idx<rt_idx )
            {
                int curr_sum = num[lf_idx] + num[rt_idx];
                if ( attemp_sum < curr_sum )
                {
                    --rt_idx;
                }
                else if (curr_sum < attemp_sum)
                {
                    ++lf_idx;
                } 
                else
                {
                    if (triplet[0]!=num[tar_idx] || triplet[1]!=num[lf_idx])
                    {
                        triplet[0] = num[tar_idx];
                        triplet[1] = num[lf_idx];
                        triplet[2] = num[rt_idx];
                        results.push_back(triplet);
                    }

                    while (num[lf_idx+1]==num[lf_idx])
                    {
                        ++lf_idx;
                    }
                    ++lf_idx;
                    while (num[rt_idx-1]==num[rt_idx])
                    {
                        --rt_idx;
                    }
                    --rt_idx;
                }
            }

            while ((tar_idx+1)<vec_size && num[tar_idx+1]==num[tar_idx])
            {
                ++tar_idx;
            }
            ++tar_idx;
        }

        return results;
    }

    std::vector<std::vector<int> > TripletsSumToZero(std::vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        using namespace std;
        vector< vector<int> > results;
        sort(num.begin(), num.end());
        vector<int> triplet(3, INT_MIN);
        int curr_sum;
        for(int i=0; i<(int)num.size(); ++i)
        {
            if ( i==0 || num[i]!=num[i-1] )
            {
                int attemp_sum = -num[i];
                int lf_idx = i+1;
                int rt_idx = num.size()-1;
                while ( lf_idx<rt_idx )
                {
                    curr_sum = num[lf_idx] + num[rt_idx];
                    if ( attemp_sum < curr_sum )
                    {
                        --rt_idx;
                    }
                    else if (curr_sum < attemp_sum)
                    {
                        ++lf_idx;
                    } 
                    else
                    {
                        if (triplet[0]!=num[i] || triplet[1]!=num[lf_idx])
                        {
                            triplet[0] = num[i];
                            triplet[1] = num[lf_idx];
                            triplet[2] = num[rt_idx];
                            results.push_back(triplet);
                        }
                        --rt_idx;
                    }
                }
            }
        }

        return results;
    }

    std::vector<std::vector<int> > TripletSum(std::vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        using namespace std;

        vector< vector<int> > results;
        if (num.empty())
        {
            return results;
        }

        sort(num.begin(), num.end());
        vector<int> numbers;
        int prev = num[0];
        int count = 1;
        numbers.push_back(num[0]);
        bool existTripleZero = false;
        for (int i=1; i<(int)num.size(); ++i)
        {
            if (num[i] == prev)
            {
                ++count;
                if (prev!=0 && count<=2) // selective here
                {
                    numbers.push_back(num[i]);
                }
                else
                {
                    if (prev==0 && count>=3 && existTripleZero==false)
                    {
                        existTripleZero = true;
                    }
                }
            } 
            else
            {
                prev = num[i];
                count = 1;
                numbers.push_back(num[i]);
            }
        }

        vector<int> triplet(3, 0);
        if (existTripleZero)
        {
            results.push_back(triplet);
        }

        int curr_sum;
        for(int i=0; i<(int)numbers.size(); ++i)
        {
            if ( i==0 || numbers[i]!=numbers[i-1] )
            {
                int attemp_sum = -numbers[i];
                int lf_idx = i+1;
                int rt_idx = numbers.size()-1;
                while ( lf_idx<rt_idx )
                {
                    curr_sum = numbers[lf_idx] + numbers[rt_idx];
                    if ( attemp_sum < curr_sum )
                    {
                        --rt_idx;
                    }
                    else if (curr_sum < attemp_sum)
                    {
                        ++lf_idx;
                    } 
                    else
                    {
                        if (triplet[0]!=numbers[i] || triplet[1]!=numbers[lf_idx])
                        {
                            triplet[0] = numbers[i];
                            triplet[1] = numbers[lf_idx];
                            triplet[2] = numbers[rt_idx];
                            results.push_back(triplet);
                        }
                        --rt_idx;
                    }
                }
            }
        }

        return results;
    }


};

int main(int argc, char* argv)
{
    int array[] = { -4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6 };
    std::vector<int> nums(array, array+sizeof(array)/sizeof(array[0]));

    Solution solver;
    std::vector<std::vector<int> > testres = solver.TripletsSumToZero(nums);
    
    std::vector<std::vector<int> > results = solver.TripsSumToZero(nums);

    return 0;
}