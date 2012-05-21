#include <iostream>
#include <string>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    string minWindow(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(S.empty() || T.empty()) return string();

        // Init local variables
        int desti[CHAR_MAX-CHAR_MIN+1] = {0};
        for(int i=0; i<T.size(); ++i) {++desti[T[i]-CHAR_MIN];}
        int recs[CHAR_MAX-CHAR_MIN+1] = {0};
        int count = 0;
        int winsize = 0;
        // find the 1st match
        for(int i=0; i<S.size() && count<T.size(); ++i) {
            if(recs[S[i]-CHAR_MIN]++ < desti[S[i]-CHAR_MIN]) {++count;}
            ++winsize;
        }
        if(count<T.size()) { return string(); }

        // search for better window
        int lfi = 0;
        int rti = winsize;
        while(recs[S[lfi]-CHAR_MIN]>desti[S[lfi]-CHAR_MIN]) {
            --recs[S[lfi]-CHAR_MIN];
            ++lfi;
        }
        int winstart = lfi;
        winsize = winsize - lfi;
        for(; rti<S.size() && winsize>T.size(); ++rti) {
            ++recs[S[rti]-CHAR_MIN];
            while(recs[S[lfi]-CHAR_MIN]>desti[S[lfi]-CHAR_MIN]) {
                --recs[S[lfi]-CHAR_MIN];
                ++lfi;
            }
            if(rti-lfi+1<winsize) {
                winsize = rti-lfi+1;
                winstart=lfi;
            }
        }

        return S.substr(winstart, winsize);
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    Solution solver;

    string teststr = "bba";
    string targetstr = "ab";

    string resultstr = solver.minWindow(teststr, targetstr);

    return 0;
}