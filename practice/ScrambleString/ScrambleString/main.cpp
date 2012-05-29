#include <iostream>
#include <string>
#include <vector>

using namespace std;

// naiive version, for better version see the next version
bool IsScrambleNaiive(string s1, string s2) {
    if(s1.size() != s2.size()) return false;
    if (s1.empty() && s2.empty()) return true;
    int strsize = s1.size();
    if(strsize==1) return s1[0]==s2[0];

    for(int div=1; div<strsize; ++div) {
        if( IsScrambleNaiive(s1.substr(0, div), s2.substr(0, div))
            && IsScrambleNaiive(s1.substr(div, strsize-div), s2.substr(div, strsize-div)) )
        {
            return true;
        }

        if( IsScrambleNaiive(s1.substr(0, div), s2.substr(strsize-div, div))
            && IsScrambleNaiive(s1.substr(div, strsize-div), s2.substr(0, strsize-div)) )
        {
            return true;
        }
    }
    return false;
}

class Solution {
public:
    bool isScramble(string s1, string s2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(s1.size() != s2.size()) return false;
        if (s1.empty() && s2.empty()) return true;

        int strsize = s1.size();
        recone.resize(strsize+1, 0);
        rectwo.resize(strsize+1, 0);
        for (int i=0; i<strsize; ++i) {
            recone[i+1] = recone[i]+(int)s1[i];
            rectwo[i+1] = rectwo[i]+(int)s2[i];
        }

        return IsScramble(0, 0, strsize);
    }

private:
    vector<int> recone;
    vector<int> rectwo;

    bool IsScramble(int lfone, int lftwo, int strsize) {
        if (strsize==1) return recone[lfone+1]-recone[lfone]==rectwo[lftwo+1]-rectwo[lftwo];

        if (recone[lfone+strsize]-recone[lfone] != rectwo[lftwo+strsize]-rectwo[lftwo]) {
            return false;
        }
        for (int div=1; div<strsize; ++div) {
            if (IsScramble(lfone, lftwo, div) && IsScramble(lfone+div, lftwo+div, strsize-div)) {
                return true;
            }
            if (IsScramble(lfone, lftwo+strsize-div, div) && IsScramble(lfone+div, lftwo, strsize-div)) {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char** argv)
{
    Solution solver;
    string sone = "abc";
    string stwo = "bca";

    bool isscramble = solver.isScramble(sone, stwo);

    return 0;
}