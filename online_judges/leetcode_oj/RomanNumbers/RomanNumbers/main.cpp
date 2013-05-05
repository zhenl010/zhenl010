#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

// Caveat: Only support numbers between 1 and 3999
template <int N> // number of int digits
class RomanNumber {
public:
  RomanNumber(char romans[2*N+1] = "IVXLCDM??") {
    copy(romans, romans+2*N+1, romans_);
    int val = 1;
    for (int i=0; i<N; ++i) {
      vals_[romans_[2*i]] = val;
      vals_[romans_[2*i+1]] = 5*val;
      val *= 10;
    }
  }

  int romanToInt(const string &s) {
    int num = 0;
    size_t idx = 0;
    while (idx < s.size()) {
      if (idx+1 < s.size() && vals_[s[idx]]<vals_[s[idx+1]]) {
        num += vals_[s[idx+1]] - vals_[s[idx]];
        idx += 2;
      } else {
        num += vals_[s[idx++]];
      }
    }
    return num;
  }

  string intToRoman(int num) {
    string str;
    for (int pos=0; 0<num; ++pos, num/=10) {
      int x = num % 10;
      str = getRoman(x, pos) + str;
    }

    return str;
  }

private:
  string getRoman(int x, int pos) {
    string roman;
    if (x==9) return roman + romans_[2*pos] + romans_[2*(pos+1)];
    if (x==4) return roman + romans_[2*pos] + romans_[2*pos+1];
    if (x>=5) { roman += romans_[2*pos+1]; x-=5; }
    return roman + string(x, romans_[2*pos]);
  }

  char romans_[2*N+1];
  unordered_map<char, int> vals_;
};

// Caveat: Only support numbers between 1 and 3999
class Solution {
public:
  int romanToInt(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return roman_.romanToInt(s);
  }

  string intToRoman(int num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return roman_.intToRoman(num);
  }

private:
  RomanNumber<4> roman_;
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;
  int num = 3999;
  string roman = solver.intToRoman(num);


  return 0;
}