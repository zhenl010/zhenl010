#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string CountAndSay(string& str) {
        string result;
        int count = 1;
        for(int i=1; i<str.size(); ++i)
        {
            if(str[i] == str[i-1])
            {
                ++count;
            }
            else
            {
                stringstream strstm;
                strstm << count << str[i-1];
                result += strstm.str();
                count=1;
            }
        }
        stringstream strstm;
        strstm << count << str[str.size()-1];
        result += strstm.str();
        return result;
    }

    string countAndSay(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string str;
        if(n<1) return str;
        str = "1";
        for(int i=1; i<n; ++i)
        {
            str = CountAndSay(str);
        }
        return str;
    }    
};

int main(int argc, char** argv)
{
    Solution solver;

    string nthstr = solver.countAndSay(4);

    return 0;
}