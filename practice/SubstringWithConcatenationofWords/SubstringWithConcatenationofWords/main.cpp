#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> results;
        if(S.empty() || L.empty() || L.begin()->empty()) return results;

        strsize = S.size();
        wordlength = L.begin()->size();
        wordnum = L.size();
        unordered_map<string, int> targetwords;
        for (int i=0; i<wordnum; ++i) {
            if (targetwords.find(L[i]) != targetwords.end()) {
                ++targetwords[L[i]];
            } else {
                targetwords[L[i]]=1;
            }
        }

        for(int i=0; i<=strsize-wordlength*wordnum; ++i) {
            if( IsMatch(S, i, targetwords) ) {
                results.push_back(i);
            }
        }
        return results;
    }

private:
    bool IsMatch(const string& str, int startid, unordered_map<string, int>& targetwords) {
        unordered_map<string, int> wordcounts;
        for(int i=0; i<wordnum; ++i) {
            string locstr = str.substr(startid, wordlength);
            if(targetwords.find(locstr) == targetwords.end()) { return false; }
            if (wordcounts.find(locstr) != wordcounts.end()) {
                ++wordcounts[locstr];
            } else {
                wordcounts[locstr] = 1;
            }
            if (wordcounts[locstr] > targetwords[locstr]) { return false; }
            startid += wordlength;
        }
        return true;
    }

    // private data:
    int strsize;
    int wordlength;
    int wordnum;
};

class SolutionMemorized {
private:
    // private data:
    int strsize;
    int wordlength;
    int wordnum;

public:
    vector<int> findSubstring(string S, vector<string> &L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> results;
        if(S.empty() || L.empty() || L.begin()->empty()) return results;

        strsize = S.size();
        wordlength = L.begin()->size();
        wordnum = L.size();
        unordered_map<string, int> targetwords;
        for (int i=0; i<wordnum; ++i) {
            if (targetwords.find(L[i]) != targetwords.end()) {
                ++targetwords[L[i]];
            } else {
                targetwords[L[i]]=1;
            }
        }

        unordered_map<string, int> knownwords;
        int wordid = 0;
        for (unordered_map<string, int>::iterator itr=targetwords.begin(); itr!=targetwords.end(); ++itr) {
            knownwords[itr->first] = wordid++;
        }

        vector<int> targetids(wordid);
        for (unordered_map<string, int>::iterator itr=targetwords.begin(); itr!=targetwords.end(); ++itr) {
            targetids[knownwords[itr->first]] = itr->second;
        }

        vector<int> recids(S.size()-wordlength+1);
        for (int i=0; i<=(int)S.size()-wordlength; ++i)
        {
            string locstr = S.substr(i,wordlength);
            if (knownwords.find(locstr) != knownwords.end()) {
                recids[i] = knownwords[locstr];
            } else {
                recids[i] = -1; // invalid array index
            }
        }

        for(int i=0; i<=strsize-wordlength*wordnum; ++i) {
            if( IsMatch(recids, i, targetids) ) {
                results.push_back(i);
            }
        }
        return results;
    }

private:
    bool IsMatch(const vector<int>& recids, int startid, const vector<int>& targetids) const {
        vector<int> wordcounts(targetids.size(), 0);
        for (int i=0; i<wordnum; ++i) {
            if (recids[startid]<0 || wordcounts[recids[startid]]==targetids[recids[startid]]) { return false; }
            ++wordcounts[recids[startid]];
            startid += wordlength;
        }
        return true;
    }
};

int main(int argc, char** argv)
{
    SolutionMemorized solver;

    string str = "barfoothefoobarman";
    vector<string> words;
    words.push_back("foo");
    words.push_back("bar");

    vector<int> matchs = solver.findSubstring(str, words);

    return 0;
}