// Given an absolute path for a file (Unix-style), simplify it.
// 
// For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"
// Corner Cases:
// Did you consider the case where path = "/../"?
// In this case, you should return "/".
// Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
// In this case, you should ignore redundant slashes and return "/home/foo".
#include <iostream>
#include <string>
#include <list>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        path += "/"; // dummy path end
        list<string> strkeeper;
        size_t prv = 0;
        size_t pos = path.find_first_of("/", prv);
        while (pos != string::npos) {
            string str = path.substr(prv, pos-prv);
            if (str=="..") {
                if (!strkeeper.empty()) { strkeeper.pop_back(); }
            } else {
                if (!str.empty() && str!=".") { strkeeper.push_back("/"+str); }
            }

            prv = pos+1;
            pos = path.find_first_of("/", prv);
        }

        path = strkeeper.empty() ? "/" : "";
        for (auto itr=strkeeper.begin(); itr!=strkeeper.end(); ++itr) {
            path += *itr;
        }
        return path;
    }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
    Solution solver;

    string path = "/.hidden";

    string newpath = solver.simplifyPath(path);

    return 0;
}