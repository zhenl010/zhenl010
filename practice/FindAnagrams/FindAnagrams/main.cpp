#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <map>

using namespace std;

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector< vector<int> > sigs(strs.size());
        for (int i=0; i<strs.size(); ++i)
        {
            string str = strs[i];
            vector<int> count(26, 0);
            for (int j=0; j<str.size(); ++j)
            {
                ++count[str[j]-'a'];
            }
            sigs[i] = count;
        }

        map<vector<int>, int> sig_map;
        for (int i=0; i<strs.size(); ++i)
        {
            if (sig_map.find(sigs[i]) == sig_map.end())
            {
                sig_map[sigs[i]] = 0;
            } 
            else
            {
                ++sig_map[sigs[i]];
            }
        }

        vector<string> anags;
        for (int i=0; i<strs.size(); ++i)
        {
            if (sig_map[sigs[i]] > 0)
            {
                anags.push_back(strs[i]);
            }
        }

        return anags;
    }
};

int main(int argc, char** argv)
{
    using namespace std;

    vector<int> v1(26);
    vector<int> v2(26);
    v2[13] = 1;

    if (v1 < v2)
    {
        cout << "smaller vectors" << endl;
    }

    map< vector<int>, int > sig_map;

    return 0;
}