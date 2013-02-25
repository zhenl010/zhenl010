#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

// assume helper functions defined already
bool isPrefix(const string& str) { return str.size()<6; }
bool isWord(const string& str) { return str.size()>5; }

template<int M, int N>
void FindBoggleWords(const char grid[M][N], vector<string>& words, int row, int col,
                     string& curr_str, unordered_set<const char*>& covered) {
    if (covered.find(&grid[row][col]) != covered.end()) return; // current element already been used
    
    curr_str += grid[row][col];
    covered.insert(&grid[row][col]);
    if (isWord(curr_str)) words.push_back(curr_str); // add to result if valid word
    if (isPrefix(curr_str)) { // search further
        for (int i=max(0,row-1); i<min(N,row+2); ++i) {
            for (int j=max(0,col-1); j<min(N,col+2); ++j) {
                // recursively search further
                FindBoggleWords<M,N>(grid, words, i, j, curr_str, covered);
            }
        }
    }
    curr_str.erase(curr_str.size()-1); // remove the last character added earlier
    covered.erase(&grid[row][col]);
}

template<int M, int N>
vector<string> BoggleWords(const char grid[M][N]) {
    vector<string> results;
    for (int row=0; row<M; ++row) {
        for (int col=0; col<N; ++col) {
            string str;
            unordered_set<const char*> covered;
            FindBoggleWords<M, N>(grid, results, row, col, str, covered);
        }
    }
    return results;
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    const int BOGGLE_ROW_NUM = 4;
    const int BOGGLE_COL_NUM = 4;
    char boggle_grid[BOGGLE_ROW_NUM][BOGGLE_COL_NUM] = {
        { 'a', 'b', 'c', 'd' },
        { 'e', 'f', 'g', 'h' },
        { 'i', 'j', 'k', 'l' },
        { 'm', 'n', 'o', 'p' },
    };

    vector<string> boggle_words = BoggleWords<BOGGLE_ROW_NUM, BOGGLE_COL_NUM>(boggle_grid);

    return 0;
}