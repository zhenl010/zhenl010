#include <iostream>
#include <vector>
#include <set>
#include "sliding_window_min.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace augment_data_structure;

    const int winsize = 20;
    SlidingWindowMin<int, winsize> slidingwindow;

    vector<int> nums;
    vector<int> mins;
    const int TEST_INPUT_SIZE = INT_MAX/(1<<20);
    for (int i=0; i<TEST_INPUT_SIZE; ++i)
    {
        int curr = rand() % 100;
        nums.push_back(curr);
        slidingwindow.PushBack(curr);
        mins.push_back(slidingwindow.CurrentMin());
    }

    // automated correctness check (very naiive)
    for (int i=0; i<TEST_INPUT_SIZE; ++i)
    {
        set<int> localset;
        for (int j=max(0,i-winsize+1); j<=i; ++j)
        {
            localset.insert(nums[j]);
        }
        if (mins[i] != *(localset.begin()))
        {
            cout << "WRONG RESULT!";
        }
    }

    /*
    // output stream and window minimums
    for (int i=0; i<TEST_INPUT_SIZE; ++i)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    for (int i=0; i<TEST_INPUT_SIZE; ++i)
    {
        cout << mins[i] << " ";
    }
    */

    cout << "Passed all tests!!!" << endl;

    return 0;
}