#include <iostream>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
public:
  bool isPalindrome(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (s.empty()) return true;

    int n = s.size();
    int l = 0;
    int r = s.size()-1;
    while (l<r) {
      while (l<n && !isValid(s[l])) { ++l; }
      while (r>=0 && !isValid(s[r])) { --r; }
      if (l<r && !equal(s[l++], s[r--])) return false;
    }
    return true;
  }

private:
  static bool isValid(char c) {
    return ('a'<=c && c<='z') || ('0'<=c && c<='9') || ('A'<=c && c<='Z');
  }

  static bool equal(char a, char b) {
    return a==b || (a-'a' == b-'A') || (a-'A' == b-'a');
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  Solution solver;

  string str = "a";

  bool is_palindrome = solver.isPalindrome(str);

  return 0;
}