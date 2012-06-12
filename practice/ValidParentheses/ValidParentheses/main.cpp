//////////////////////////////////////////////////////////////////////////
// Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        const int BRAC_TYPE_NUM = 3;
        stack<int> lps[3];
        char ptypes[CHAR_MAX-CHAR_MIN+1];
        ptypes['('] = 0;
        ptypes[')'] = 0;
        ptypes['['] = 1;
        ptypes[']'] = 1;
        ptypes['{'] = 2;
        ptypes['}'] = 2;
        bool isleft[CHAR_MAX-CHAR_MIN+1];
        isleft['('] = true;
        isleft[')'] = false;
        isleft['['] = true;
        isleft[']'] = false;
        isleft['{'] = true;
        isleft['}'] = false;
        int strsize = s.size();
        for(int i=0; i<strsize; ++i) {
            if(isleft[s[i]]) {
                lps[ptypes[s[i]]].push(i);
            } else {
                if(lps[ptypes[s[i]]].empty()) { return false; }
                int lfi = lps[ptypes[s[i]]].top();
                for(int bractype=0; bractype<BRAC_TYPE_NUM; ++bractype) {
                    if (bractype != ptypes[s[i]]) {
                        if (lps[bractype].empty()!=true && lps[bractype].top()>lfi) {
                            return false;
                        }
                    }
                }
                lps[ptypes[s[i]]].pop();
            }
        }

        bool isvalid = true;
        for(int i=0; i<BRAC_TYPE_NUM; ++i) {
            if(lps[i].empty() != true) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    return 0;
}