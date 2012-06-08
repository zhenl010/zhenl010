#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> lines;
        if (words.empty()) { return lines; }

        int lfi = 0;
        int totl = words[lfi].size();
        int rti = 1;
        int wscount = 0;
        while(rti<words.size()) {
            if(totl+wscount+1+words[rti].size() > L) { // notice the equal sign here
                // add white spaces
                lines.push_back(AddSpacesFully(lfi, rti-1, words, L-totl));
                lfi = rti;
                totl = words[rti].size();
                wscount = 0;
            } else {
                totl = totl + (words[rti]).size(); // considering space added
                ++wscount;
            }
            ++rti;
        }
        lines.push_back(AddSpacesLeft(lfi, rti-1, words, L-totl));

        return lines;
    }

private:
    string AddSpacesFully(int lfi, int rti, vector<string> &words, int wsn) {
        if (lfi == rti) { // special case
            return words[lfi] + string(wsn, ' ');
        }

        string line;
        int itn = rti-lfi;
        int smws = wsn/itn;
        int mid = wsn%itn;
        string wsadd(smws, ' ');
        for(int idx=lfi; idx<lfi+mid; ++idx) {
            line += words[idx] + wsadd + " ";
        }
        for(int idx=lfi+mid; idx<rti; ++idx) {
            line += words[idx] + wsadd;
        }
        line += words[rti];
        return line;
    }

    string AddSpacesLeft(int lfi, int rti, vector<string> &words, int wsn) {
        string line;
        for(int idx=lfi; idx<rti; ++idx) {
            line += words[idx] + " ";
            --wsn;
        }
        return line + words[rti] + string(wsn, ' ');
    }
};

int main(int argc, char** argv) {
    Solution solver;
    const char* strs[] = {
        "a","b","c","d","e"
    };
    int JustfyLength = 3;

    vector<string> words(sizeof(strs)/sizeof(char*));
    for (int i=0; i<words.size(); ++i) {
        words[i] = strs[i];
    }
    vector<string> fmwords = solver.fullJustify(words, JustfyLength);

    return 0;
}