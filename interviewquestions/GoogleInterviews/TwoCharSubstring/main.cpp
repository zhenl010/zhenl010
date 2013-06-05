#include <iostream>
#include <string>
#include <set>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

// Given a string, find longest substring which contains no more than two
// unique characters.
typedef unsigned int uint;
struct SubSeg{ char c1; char c2; uint p1; uint p2; uint l; };
string LongestTwoChar(const string& str) {
  if (str.empty()) return string(); // 0 char

  SubSeg substr = { str[0], str[0], 0, 0, 1 };
  SubSeg longest = substr;
  for (uint i=1; i<str.size(); ++i) {
    if (str[i]==substr.c1 || str[i]==substr.c2) {
      ++substr.l;
      if (str[substr.p2]!=str[i]) { substr.p2 = i; }
    } else {
      SubSeg next = { str[substr.p2], str[i], substr.p2, i, i-substr.p2+1 };
      substr = next;
    }

    if (longest.l < substr.l) {
      longest = substr;
    }
  }

  return str.substr(longest.p1, longest.l);
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  string str = "aaabbbaaccccccccaa";
  string substr = LongestTwoChar(str);

  return 0;
}