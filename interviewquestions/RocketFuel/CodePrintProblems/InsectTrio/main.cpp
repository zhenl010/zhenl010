#include <iostream>
#include <string>

namespace {
//////////////////////////////////////////////////////////////////////////
using namespace std;

class Solution {
public:
  static const int kGrpNum = 3;
  // assume insects are 'a', 'b', or 'c' exclusively
  static int NumRemain(const string& insects) {
    int nums[kGrpNum] = {0};
    for (auto itr=insects.begin(); itr!=insects.end(); ++itr) {
      ++nums[*itr-'a'];
    }
    
    int grp_num = 0;
    for (int i=0; i<kGrpNum; ++i) {
      if (0<nums[i]) { ++grp_num; }
    }
    if (grp_num==1) return insects.size();

    bool same_oddness = (nums[0]%2 == nums[kGrpNum-1]%2);
    for (int i=1; same_oddness&&i<kGrpNum; ++i) {
      same_oddness &= (nums[i]%2 == nums[i-1]%2);
    }

    return same_oddness ? 2 : 1;
  }
};

//////////////////////////////////////////////////////////////////////////
}

int main() {
  int num;
  cin >> num;
  string str;
  while (num>0) {
    cin >> str;
    --num;
    printf("%d\n", Solution::NumRemain(str));
  }

  return 0;
}