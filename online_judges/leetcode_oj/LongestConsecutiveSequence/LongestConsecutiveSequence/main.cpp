// Longest Consecutive SequenceFeb 14
// Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
// 
// For example,
// Given [100, 4, 200, 1, 3, 2],
// The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
// 
// Your algorithm should run in O(n) complexity.
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

template<typename T, int N>
int ArraySize(T(&a)[N]) { return N; }

class Solution {
public:
    // basically Peking2's solution...
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_set<int> uniques;
        for (int x:num) { uniques.insert(x); }

        int cnt, l, r, longest = 0;
        for (int x:num) {
            if (uniques.find(x) != uniques.end()) {
                cnt = 1;
                l = x-1;
                while (uniques.find(l) != uniques.end()) { ++cnt; uniques.erase(uniques.find(l--)); }
                r = x+1;
                while (uniques.find(r) != uniques.end()) { ++cnt; uniques.erase(uniques.find(r++)); }
                uniques.erase(uniques.find(x));
                longest = max(longest, cnt);
            }
        }

        return longest;
    }

public:
    int longestConsecutiveLong(vector<int> &num) { // long code ...
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_map<int, IntRange> ranges;
        int longest = 0;

        int x; // speed up?
        for (size_t i=0; i<num.size(); ++i) {
            x = num[i];
            if (ranges.find(x) != ranges.end()) continue; // repeated element

            if (ranges.find(x+1)!=ranges.end() && ranges.find(x-1)!=ranges.end()) {
                ranges[ranges[x-1].min].max = ranges[x+1].max;
                ranges[ranges[x+1].max].min = ranges[x-1].min;
                longest = max(longest, Length(ranges[ranges[x-1].min]));
                ranges[x] = ranges[ranges[x-1].min];
            } else if (ranges.find(x-1)!=ranges.end()) {
                ranges[ranges[x-1].min].max = x;
                ranges[x] = ranges[ranges[x-1].min];
                longest = max(longest, Length(ranges[x]));
            } else if (ranges.find(x+1)!=ranges.end()) {
                ranges[ranges[x+1].max].min = x;
                ranges[x] = ranges[ranges[x+1].max];
                longest = max(longest, Length(ranges[x]));
            } else { // new range
                IntRange loner = { x, x };
                ranges[x] = loner;
                longest = max(longest, Length(loner));
            }
        }

        return longest;
    }

private:
    struct IntRange { int min; int max; };
    static int Length(const IntRange& range) { return range.max - range.min + 1; }

//////////////////////////////////////////////////////////////////////////
// Peking2's solution:
    //////////////////////////////////////////////////////////////////////////
public:
    int longestConsecutiveLength(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_set<int> hs;
        for(int v:num) hs.insert(v);
        int ans=0;

        for(int v:num) {
            if(hs.find(v) != hs.end()) {
                ans=max(ans,getCount(hs, v, false)+getCount(hs, v+1, true));
            }
        }
        return ans; 
    }

private:
    int getCount(unordered_set<int>& hs, int v, bool asc){
        int count=0;
        while(hs.find(v) != hs.end()){
            hs.erase(hs.find(v));
            ++count;
            v = asc ? v+1 : v-1;
        }
        return count;
    }
};

//////////////////////////////////////////////////////////////////////////
}


int main() {
    Solution solver;

    int num_arry[] = {
        // 4,2,2,-4,0,-2,4,-3,-4,-4,-5,1,4,-9,5,0,6,-8,-1,-3,6,5,-8,-1,-5,-1,2,-9,1
        9,-8,9,8,-7,9,-4,6,5,5,6,7,-9,-5,-4,6,-8,-1,8,0,1,5,4
    };
    vector<int> nums(num_arry, num_arry+ArraySize(num_arry));

    int longest = solver.longestConsecutive(nums);

    sort(nums.begin(), nums.end());

    return 0;
}