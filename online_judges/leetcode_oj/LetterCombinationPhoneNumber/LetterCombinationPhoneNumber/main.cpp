#include <iostream>
#include <string>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        size_ = digits.size();
        nums_.resize(size_);
        for (int i=0; i<size_; ++i) nums_[i] = digits[i]-'0';
        str_ = digits;
        combos_.clear();
        getCombos(0);
        return combos_;
    }

private:
    static const string kLetters[];

    void getCombos(int idx) {
        if (idx==size_) {
            combos_.push_back(str_);
        } else {
            for (size_t i=0; i<kLetters[nums_[idx]].size(); ++i) {
                str_[idx] = kLetters[nums_[idx]][i];
                getCombos(idx+1);
            }
        }
    }

    int size_;
    vector<char> nums_;
    vector<string> combos_;
    string str_;
};

const string Solution::kLetters[] = {
    " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    string str = "2";
    vector<string> combos = solver.letterCombinations(str);

    return 0;
}