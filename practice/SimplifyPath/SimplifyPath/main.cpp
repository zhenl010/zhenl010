//////////////////////////////////////////////////////////////////////////
// Given an absolute path for a file (Unix-style), simplify it.
// For example,
// path = "/home/", => "/home"
// path = "/a/./b/../../c/", => "/c"
// Corner Cases:
// Did you consider the case where path = "/../"?
// In this case, you should return "/".
// Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
// In this case, you should ignore redundant slashes and return "/home/foo".
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        static const string CURRENT_DIR = ".";
        static const string UP_LEVEL_DIR = "..";

        int pos = path.find_first_of('/')+1;    
        int edge = path.find_first_of('/', pos);

        list<string> recs;
        while(edge != string::npos) {
            string curr = path.substr(pos, edge-pos);
            if (curr == "..") {
                if (!recs.empty()) recs.pop_back();
            } else if (!curr.empty() && curr!="." && curr!="/") {
                recs.push_back(curr);
            } 
            pos = edge+1;
            edge = path.find_first_of('/', pos);
        }
        if (pos<path.size()) {
            string curr = path.substr(pos, path.size()-pos);
            if (curr == "..") {
                if (!recs.empty()) recs.pop_back();
            } else if (!curr.empty() && curr!="." && curr!="/") {
                recs.push_back(curr);
            } 
        }

        string simplepath;
        for (list<string>::iterator itr=recs.begin(); itr!=recs.end(); ++itr) {
            simplepath += '/';
            simplepath += *itr;
        }

        return simplepath.empty() ? string(1, '/') : simplepath;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    string path = "/home/./foo";
    string simpath = solver.simplifyPath(path);

    return 0;
}