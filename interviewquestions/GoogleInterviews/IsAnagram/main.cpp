#include <iostream>
#include <string>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

const int kCharNum = 256;

bool IsPalindrome(const string& s1, const string& s2) {
  if(s1.size() != s2.size()) return false;
  if(s1.size()==0) return true;

  vector<int> ct1(kCharNum, 0);
  vector<int> ct2(kCharNum, 0);

  for (size_t i=0; i<s1.size(); ++i) {
    ++ct1[s1[i]];
    ++ct2[s2[i]];
  }

  return ct1 == ct2;
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  string s1 = "aaaabca";
  string s2 = "cbaaaaa";

  bool is_ana = IsPalindrome(s1, s2);

  return 0;
}