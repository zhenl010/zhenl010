//////////////////////////////////////////////////////////////////////////
// Given a string S, find the longest palindromic substring in S.
// Here, we discuss an algorithm that runs in O(N) time and O(N) space,
//   also known as Manacher’s algorithm.
//////////////////////////////////////////////////////////////////////////
#ifndef LONGEST_PALINDROMIC_SUBSTRING_H_
#define LONGEST_PALINDROMIC_SUBSTRING_H_

#include <string>
#include <vector>

class LpsSolver
{
public:
    std::string LongestPalindrome(const std::string&);

private:
};

#endif