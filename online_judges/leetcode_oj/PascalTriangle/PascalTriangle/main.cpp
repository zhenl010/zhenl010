#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class Solution {
public:
  vector<vector<int> > generate(int numRows) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (numRows < 1) return vector<vector<int> >();

    vector<vector<int> > rows(numRows);
    rows[0] = vector<int>(1, 1);
    for (int i=1; i<numRows; ++i) {
      rows[i] = vector<int>(i+1, 1);
      for (int j=1; j<i; ++j) {
        rows[i][j] = rows[i-1][j-1] + rows[i-1][j];
      }
    }
    return rows;
  }

  vector<int> getRow(int rowIndex) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    ++rowIndex; // row index starts from 0 ...
    if (rowIndex < 1) return vector<int>();

    vector<vector<int> > rows(2, vector<int>(rowIndex, 1));
    int prev = 0; int curr = 1;
    for (int i=1; i<rowIndex; ++i) {
      for (int j=1; j<i; ++j) {
        rows[curr][j] = rows[prev][j-1] + rows[prev][j];
      }
      swap(prev, curr);
    }
    return rows[prev];
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;

  int rownum = 5;
  vector<vector<int> > triangle = solver.generate(rownum);

  return 0;
}