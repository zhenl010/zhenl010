#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minCutDp(string s) { // dp
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(s.empty()) return 0; // special case

        GetLengths(s);

        vector<int> cuts(size_+1, size_); // init
        cuts[0] = 0; // init
        for (size_t l=1; l<=size_; ++l) {
            for (size_t i=0; i<lengths_[size_-l].size(); ++i) {
                cuts[l] = min(cuts[l], 1+cuts[l-lengths_[size_-l][i]]);
            }
        }

        return cuts[size_] - 1;
    }

    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(s.empty()) return 0; // special case

        GetLengths(s);

        vector<int> cuts(size_+1, -1); // -1 as never visited
        queue<size_t> nodes;
        nodes.push(0);
        cuts[0] = 0;
        size_t pos = 0;
        while(!nodes.empty()) {
            pos = nodes.front();
            nodes.pop();

            if(pos != size_) { // end points reached
                // for (size_t i=0; i<lengths_[pos].size(); ++i) {
                for (int i=(int)(lengths_[pos].size()-1); i>=0; --i) {
                    if(cuts[pos+lengths_[pos][i]] == -1) {
                        cuts[pos+lengths_[pos][i]] = cuts[pos] + 1;
                        nodes.push(pos+lengths_[pos][i]);
                    }
                }
            }
        }

        return cuts[size_] - 1;
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        if(s.empty()) return results;

        GetLengths(s);
        vector<string> partition;
        GetPartitions(s, 0, partition, 0, results);

        return results;
    }

private:
    void GetPartitions(const string& str, size_t pos, vector<string>& partition, size_t part_id,
        vector<vector<string>>& results) {
        if(pos >= str.size()) {
            results.push_back(partition);
            return;
        }

        for(size_t i=0; i<lengths_[pos].size(); ++i) {
            partition.push_back( str.substr(pos, lengths_[pos][i]) );
            GetPartitions(str, pos+lengths_[pos][i], partition, 0, results);
            partition.pop_back();
        }
    }

    void GetLengths(const string& s) {
        size_ = s.size();
        vector<vector<bool>> is_valid(size_, vector<bool>(size_));
        for(size_t i=0; i<size_; ++i) is_valid[i][i] = true;
        for(size_t i=0; i<size_-1; ++i) is_valid[i][i+1] = s[i]==s[i+1];

        for (size_t l=2; l<size_; ++l) {
            for (size_t i=0; i<size_-l; ++i) {
                is_valid[i][i+l] = is_valid[i+1][i+l-1] && s[i]==s[i+l];
            }
        }

        lengths_.clear();
        lengths_.resize(size_, vector<size_t>());
        for (size_t i=0; i<size_; ++i) {
            for(size_t j=i; j<size_; ++j) {
                if(is_valid[i][j]) lengths_[i].push_back(j-i+1);
            }
        }
    }

    unsigned int size_;
    vector<vector<size_t>> lengths_;
};

int main() {
    Solution solver;

    int min_cuts = solver.minCut("aab");

    vector<vector<string>> partitions = solver.partition("aab");

    return 0;
}