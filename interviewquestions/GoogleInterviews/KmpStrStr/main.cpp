#include <iostream>
#include <vector>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

vector<int> KmpTable(char* p, int m) {
  vector<int> t(m+1, -1);
  int i=0, j=-1;
  while(i<m) {
    while (j>-1 && p[i]!=p[j]) { j=t[j]; }
    ++i; ++j;
    if (p[i]==p[j]) {
      t[i] = t[j];
    } else {
      t[i] = j;
    }
  }

  return t;
}

char* StrStr(char* s, int n, char* p, int m) {
  vector<int> t = KmpTable(p, m);

  int i=0, j=0;
  while (i<n) {
    while (j>=0 && s[i]!=p[j]) { j=t[j]; }
    ++i; ++j;
    if (j==m) return &(s[i-j]);
  }

  return NULL;
}

void CoutStrStr(char* s, int n, char* p, int m) {
  vector<int> t = KmpTable(p, m);

  int i=0, j=0;
  while (i<n) {
    while (j>=0 && s[i]!=p[j]) { j=t[j]; }
    ++i; ++j;
    if (j==m) {
      cout << &(s[i-j]) << endl;
      j = t[j]; // explicitly set instead of using c_string '\0'
    }
  }
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
  char* str = "aabaaabaaa";
  char* pat = "aba";
  char* outstr = StrStr(str, strlen(str), pat, strlen(pat));

  cout << str << endl;
  cout << pat << endl;
  cout << outstr << endl;

  cout << endl << endl;
  CoutStrStr(str, strlen(str), pat, strlen(pat));

  return 0;
}