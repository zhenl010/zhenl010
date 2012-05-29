//////////////////////////////////////////////////////////////////////////
// Given an array of integers, find two numbers such that they add up to a specific target number.
// The function twoSum should return indices of the two numbers such that they add up to the target, 
// where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
// You may assume that each input would have exactly one solution.
// Input: numbers={2, 7, 11, 15}, target=9
// Output: index1=1, index2=2
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_map<int, size_t> numap;
        for(size_t i=0; i<numbers.size(); ++i) {
            int reqnum = target - numbers[i];
            unordered_map<int, size_t>::iterator itr = numap.find(reqnum);
            if(itr != numap.end()) { // found
                vector<int> twoids(2);
                twoids[0] = numap[reqnum];
                twoids[1] = i+1;
                return twoids;
            }

            numap[numbers[i]] = i+1;
        }
        // precondition assumes at least one result 
        throw("NO RESULT FOUND!");
    }
};

int main(int argc, char** argv) {
    return 0;
}