#include <iostream>
#include <string>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(const string& s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(s.empty()) return 0;
        
        int recs[CHAR_MAX-CHAR_MIN+1];
        std::fill_n(recs, CHAR_MAX-CHAR_MIN+1, -1);

        int lfi=0, rti=0, maxleng=1;
        recs[s[0]-CHAR_MIN]=0;
        while(lfi<s.size() && ++rti<s.size())
        {
            int prev = recs[s[rti]-CHAR_MIN];
            if(prev >= lfi) // repeated
            {
                maxleng = max(maxleng, rti-lfi);
                lfi = prev + 1;
            }
            recs[s[rti]-CHAR_MIN] = rti;
        }
        maxleng = max(maxleng, rti-lfi); // trailing substr

        return maxleng;
    }
};
    
//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    using namespace std;

    Solution solver;

    string str = "abcd";

    int maxleng = solver.lengthOfLongestSubstring(str);

    return 0;
}