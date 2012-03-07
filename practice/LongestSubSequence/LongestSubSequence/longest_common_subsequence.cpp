#include "longest_common_subsequence.h" // Preferred location
#include <string>
#include <vector>

namespace longest_common_subsequence
{
//////////////////////////////////////////////////////////////////////////

std::string LongestCommonSubquence(const std::string& strX, const std::string& strY)
{
    using namespace std;
    typedef vector< int > RowType; // or column
    typedef vector< RowType > TableType;
    TableType lcsTable;
    lcsTable.resize(strX.length()+1);
    for (TableType::iterator itoI=lcsTable.begin(); itoI!=lcsTable.end(); ++itoI)
    {
        itoI->resize(strY.length()+1, 0);
    }

    // Update all cells
    for (RowType::size_type i=1; i<lcsTable.size(); ++i)
    {
        for (RowType::size_type j=1; j<lcsTable[0].size(); ++j)
        {
            if (strX[i-1] == strY[j-1])
            {
                lcsTable[i][j]=lcsTable[i-1][j-1]+1;
            } 
            else
            {
                lcsTable[i][j]=max(lcsTable[i-1][j], lcsTable[i][j-1]);
            }
        }
    }

    // The length of the longest common subsequence:
    int lcsLength = (lcsTable.back()).back();

    // Reconstruct the subsequence back ward
    std::string result_string;
    result_string.resize(lcsLength, '\0');
    RowType::size_type i=lcsTable.size()-1;
    RowType::size_type j=lcsTable[i].size()-1;
    while ( i>0 && j>0 )
    {
        if (strX[i-1] == strY[j-1])
        {
            result_string[ lcsTable[i][j]-1 ] = strX[i-1];
            --i; --j;
        }
        else
        {
            if (lcsTable[i-1][j] < lcsTable[i][j-1])
            {
                --j;
            } 
            else
            {
                --i;
            }
        }
    }

    return result_string;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
namespace
{
//////////////////////////////////////////////////////////////////////////

void GetLcsLengths(std::vector<int>& lcs_lengths, const std::string& str_x, const std::string& str_y)
{
    using namespace std;
    lcs_lengths.resize(str_x.size()+1, 0);
    vector<int> lcs_swap(str_x.size()+1, 0);
    for (vector<int>::size_type j=0; j<str_y.size(); ++j)
    {
        for (vector<int>::size_type i=1; i<str_x.size()+1; ++i)
        {
            if (str_x[i-1]==str_y[j]) // notice there is a record for lcs(0, j)
            {
                lcs_swap[i] = lcs_lengths[i-1]+1;
            } 
            else
            {
                if (lcs_swap[i-1] < lcs_lengths[i])
                {
                    lcs_swap[i] = lcs_lengths[i];
                } 
                else
                {
                    lcs_swap[i] = lcs_swap[i-1];
                }
            }
        }
        swap(lcs_lengths, lcs_swap);
    }
}

void ForwardLcsLengths(std::vector<int>& lcs_lengths, const std::string& str_x, const std::string& str_y)
{
    GetLcsLengths(lcs_lengths, str_x, str_y);
}

void BackwardLcsLengths(std::vector<int>& lcs_lengths, const std::string& str_x, const std::string& str_y)
{
    std::string str_x_reverse(str_x);
    reverse(str_x_reverse.begin(), str_x_reverse.end());
    std::string str_y_reverse(str_y);
    reverse(str_y_reverse.begin(), str_y_reverse.end());
    GetLcsLengths(lcs_lengths, str_x_reverse, str_y_reverse);
    reverse(lcs_lengths.begin(), lcs_lengths.end());
}

int FindLcsSplit(const std::vector<int>& forwards, const std::vector<int>& backwards)
{
    ///@TODO: assert same size?
    int max_sum = INT_MIN;
    std::vector<int>::size_type split_index;
    for (std::vector<int>::size_type idx=0; idx<forwards.size(); ++idx)
    {
        int sum = forwards[idx]+backwards[idx];
        if (sum>max_sum)
        {
            max_sum = sum;
            split_index = idx;
        }
    }

    return split_index;
}


// refer to Hirschberg's algorithm - 1975
// assume strX is shorter than strY; lcs is empty
std::string GetLcsLean(const std::string& str_x, const std::string& str_y)
{
    using namespace std;
    string lcs_string;
    
    if (str_x.empty() || str_y.empty())
    {
        // result in an empty string
        lcs_string.clear();
    } 
    else
    {
        if (str_y.size() == 1)
        {
            // trivial case
            string::const_iterator sitor = str_x.begin();
            while ( sitor != str_x.end() && (*sitor) != (*str_y.begin()) )
            {
                ++sitor;
            }
            if (sitor != str_x.end())
            {
                lcs_string = string(1, (*str_y.begin()));
            } 
            else
            {
                lcs_string = string();
            }
        } 
        else
        {
            // recursive calls
            int middle = str_y.size()/2;
            string str_y_lower(str_y, 0, middle);
            string str_y_upper(str_y, middle, str_y.size()-middle);

            vector<int> lcs_forwards;
            ForwardLcsLengths(lcs_forwards, str_x, str_y_lower);
            vector<int> lcs_backwards;
            BackwardLcsLengths(lcs_backwards, str_x, str_y_upper);

            int split = FindLcsSplit(lcs_forwards, lcs_backwards);
            string str_x_left(str_x, 0, split);
            string str_x_right(str_x, split, str_x.size()-split);
            lcs_string = GetLcsLean(str_x_left, str_y_lower) + GetLcsLean(str_x_right, str_y_upper);
        }
    }

    return lcs_string;
}

//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////
std::string LongestCommonSubquenceLean(const std::string& str_x, const std::string& str_y)
{
    if (str_y.length() < str_x.length())
    {
        // without generosity let 1st string be the shorter one
        return GetLcsLean(str_y, str_x);
    }
    else
    {
        // without generosity let 1st string be the shorter one
        return GetLcsLean(str_x, str_y);
    }
}

//////////////////////////////////////////////////////////////////////////
}