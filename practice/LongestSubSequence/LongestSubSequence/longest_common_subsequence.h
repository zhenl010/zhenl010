#include <string>

namespace longest_common_subsequence
{
//////////////////////////////////////////////////////////////////////////

// lcs with O(m * n) and m * n space
std::string LongestCommonSubquence(const std::string&, const std::string&);

// lcs with O(m * n) and min(m, n) space
std::string LongestCommonSubquenceLean(const std::string& strX, const std::string& strY);

//////////////////////////////////////////////////////////////////////////
}