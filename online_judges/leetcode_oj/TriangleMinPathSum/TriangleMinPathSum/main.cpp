#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

template <typename T, int N>
int ArraySize(T(&a)[N]) { return N; }

class Solution {
public:
  int minimumTotal(vector<vector<int> > &triangle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (triangle.empty()) return 0;

    vector<vector<int> > recs(2, *triangle.rbegin());
    int prev = 0; int curr = 1;
    for (int i=triangle.size()-2; i>=0; --i) {
      for (int j=0; j<=i; ++j) {
        recs[curr][j] = triangle[i][j] + min(recs[prev][j], recs[prev][j+1]);
      }
      swap(curr, prev);
    }
    return recs[prev][0];
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;

  int tri_arr[2][2] = {
    { 1 },
    { 2, 3 }
  };
  vector<vector<int> > triangle(2);
  for (int i=0; i<ArraySize(tri_arr); ++i) {
    triangle[i] = vector<int>(tri_arr[i], tri_arr[i]+ArraySize(tri_arr[i]));
  }
  int minpath = solver.minimumTotal(triangle);

  return 0;
}