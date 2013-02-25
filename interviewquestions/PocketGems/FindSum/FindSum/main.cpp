#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;
typedef unordered_set<int> IntSet;

vector<int> twoSum(const vector<int> &nums, int target) {
    vector<int> result;
    unordered_set<int> known_nums;
    for(size_t i=0; i<nums.size(); ++i) {
        if(known_nums.find(target-nums[i]) != known_nums.end()) {
            result.push_back(target-nums[i]);
            result.push_back(nums[i]);
            return result;
        } else {
            known_nums.insert(nums[i]);
        }
    }

    return result;
}

// Helper function to find two-sum from a sorted vector
vector<int> twoSumSorted(int target, const vector<int> &nums, size_t start_id) {
    vector<int> result;

    size_t i = start_id;
    size_t j = nums.size() - 1;
    while (i < j) {
        if (nums[i]+nums[j] < target) {
            ++i;
        } else if (target < nums[i]+nums[j]) {
            --j;
        } else { // equals, found target
            result.push_back(nums[i]);
            result.push_back(nums[j]);
            return result;
        }
    }

    return result;
}

// Helper function to find three sum from a sorted vector
vector<int> threeSumSorted(int target, const vector<int> &nums, size_t start_id) {
    vector<int> result;
    for (size_t i=start_id; i<(nums.size()-2); ++i) {
        vector<int> sub_sum = twoSumSorted(target-nums[i], nums, i+1);
        if (!sub_sum.empty()) {
            result.push_back(nums[i]);
            result.insert(result.end(), sub_sum.begin(), sub_sum.end());
            return result;
        }
    }

    return result;
}

vector<int> threeSum(const vector<int> &nums, int target) {
    vector<int> numbers(nums);
    sort(numbers.begin(), numbers.end());
    return threeSumSorted(target, numbers, 0);
}

//////////////////////////////////////////////////////////////////////////
// With help of class template (function template cant get partial specialization)
//////////////////////////////////////////////////////////////////////////
template<typename T>
struct SumFinder {
    template<int N>
    static vector<T> FindSumSorted(const T &target, const vector<T> &nums, size_t start_id) {
        vector<T> result;
        for (size_t i=start_id; i<(nums.size()-N+1); ++i) {
            vector<int> sub_sum = twoSumSorted(target-nums[i], nums, i+1);
            if (!sub_sum.empty()) {
                result.push_back(nums[i]);
                result.insert(result.end(), sub_sum.begin(), sub_sum.end());
                return result;
            }
        }
        return result;
    }

    template<>
    static vector<T> FindSumSorted<2>(const T &target, const vector<T> &nums, size_t start_id) {
        vector<T> result;
        size_t i = start_id;
        size_t j = nums.size() - 1;
        while (i < j) {
            if (nums[i]+nums[j] < target) {
                ++i;
            } else if (target < nums[i]+nums[j]) {
                --j;
            } else { // equals, found target
                result.push_back(nums[i]);
                result.push_back(nums[j]);
                return result;
            }
        }
        return result;
    }
};

// Template to find N-sum
template<class T, int N>
vector<T> FindSum(const T &target, const vector<T> &nums) {
    vector<T> clone = nums;
    sort(clone.begin(), clone.end());
    return SumFinder<T>::FindSumSorted<N>(target, clone, 0);
}

//////////////////////////////////////////////////////////////////////////
}

void PrintNumbers(const vector<int> &nums) {
    if (nums.size() == 0) return;

    std::cout << nums[0];
    for (size_t i=1; i<nums.size(); ++i) {
        std::cout << " " << nums[i];
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {

    vector<int> numbers;
    for (int i=0; i<5; ++i) {
        numbers.push_back(i);
    }
    PrintNumbers(numbers);
    PrintNumbers(FindSum<int, 3>(9, numbers));

    return 0;
}