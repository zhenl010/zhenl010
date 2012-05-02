#include <vector>

/**
 * Definition for an interval.
 */
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    std::vector<Interval> insert(std::vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int numbefore = 0;
        int idx = 0;
        while(idx<intervals.size() && intervals[idx].end < newInterval.start)
        {
            ++numbefore;
            ++idx;
        }
        
        int numafter = 0;
        while(idx<intervals.size() && intervals[idx].start <= newInterval.end)
        {
            ++numafter;
            newInterval.start = std::min(intervals[idx].start, newInterval.start);
            newInterval.end = std::max(intervals[idx].end, newInterval.end);
            ++idx;
        }
        
        std::vector<Interval> results(intervals.size() - numafter + 1);
        for(int i=0; i<numbefore; ++i)
        {
            results[i] = intervals[i];
        }
        results[numbefore] = newInterval;
        for(int i=numbefore+1; i<results.size(); ++i)
        {
            results[i] = intervals[i+numafter-1];
        }
        
        return results;
    }
};

int main(int argc, char** argv)
{

    return 0;
}