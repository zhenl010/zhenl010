#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s1.size()+s2.size() != s3.size()) {
            return false;
        }

        return s1.size()<s2.size() ? isInterleaveStrs(s1,s2,s3) : isInterleaveStrs(s2,s1,s3);
    }

private:
    // precondition: s1.size<s2.size && s1.size+s2.size == s3.size
    bool isInterleaveStrs(string s1, string s2, string s3) {
        if (s1.empty()) {
            return s2 == s3;
        }

        vector<bool> bufferone(s1.size()+1, false);
        vector<bool> buffertwo(s1.size()+1, false);
        vector<bool> *ptrcurr = &buffertwo;
        vector<bool> *ptrprev = &bufferone;
        ptrcurr->at(0) = true;
        for (size_t i=1; i<=s1.size(); ++i) {
            ptrcurr->at(i) = (ptrcurr->at(i-1) && s1[i-1]==s3[i-1]);
        }

        for (size_t j=1; j<=s2.size(); ++j) {
            swap(ptrcurr, ptrprev);
            ptrcurr->at(0) = (ptrprev->at(0) && s2[j-1]==s3[j-1]);
            for (size_t i=1; i<=s1.size(); ++i) {
                ptrcurr->at(i) = (ptrcurr->at(i-1) && s1[i-1]==s3[i+j-1])
                               || (ptrprev->at(i) && s2[j-1]==s3[i+j-1]);
            }
        }

        return ptrcurr->at(s1.size());
    }
};

int main(int argc, char** argv) {
    string s1 = "a";
    string s2 = "b";
    string s3 = "ab";

    Solution solver;
    bool isInterleave = solver.isInterleave(s1, s2, s3);

    return 0;
}