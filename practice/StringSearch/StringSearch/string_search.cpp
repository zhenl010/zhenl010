#include "string_search.h"
#include <climits>

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

// Assume array sizes are real size (not including trailing '\0')
const int ALPHABET_SIZE = CHAR_MAX-CHAR_MIN+1;
const int MAX_PATTERN_SIZE = 1<<16;

inline char max ( char a, char b )
{
    return (a<b) ? b:a;
}

inline char min ( char a, char b )
{
    return (a<b) ? a:b;
}

void get_kmp_table(int* kmp_table, char* needle, int m)
{
    kmp_table[0] = -1;
    kmp_table[1] = 0;

    int pos = 2;
    int cnd = 0;

    while (pos < m)
    {
        if (needle[pos-1] == needle[cnd])
        {
            ++cnd;
            kmp_table[pos] = cnd;
            ++pos;
        } 
        else if (cnd > 0)
        {
            cnd = kmp_table[cnd];
        } 
        else
        {
            kmp_table[pos++] = 0;
        }
    }
}

void BmProcessBadSkips(int* badcharskips, char* pat, int m)
{
    int i;
    for (i=0; i<ALPHABET_SIZE; ++i)
    {
        badcharskips[i] = -1;
    }

    for (i=0; i<m; ++i)
    {
        badcharskips[pat[i]-CHAR_MIN] = i;
    }
}

void ProcessBorders(int* border, char* x, int m)
{
    border[m-1] = m;
    for (int i=m-2; i>=0; --i)
    {
        int lvl = i+1;
        while ((lvl < m) && (x[i] != x[border[lvl]-1]))
        {
            lvl = border[lvl];
        }

        if (lvl == m) // no border
        {
            border[i] = m;
        } 
        else
        {
            border[i] = border[lvl]-1;
        }
    }
}

void BmProcessGoodSkips(int* bmgoodskips, char* pat, int m)
{
    int borders[MAX_PATTERN_SIZE+1];
    ProcessBorders(borders, pat, m);

    int idx;
    int lvl;
    bmgoodskips[m-1] = 1; // Init
    for (idx=0; idx<m-1; ++idx)
    {
        bmgoodskips[idx] = borders[0];
    }

    // case one:
    for (idx=0; idx<m-1; ++idx)
    {
        lvl = idx+1;
        lvl = borders[lvl];
        while (lvl < m && pat[idx] != pat[lvl-1])
        {
            bmgoodskips[lvl-1] = lvl - idx - 1;
            lvl = borders[lvl];
        }
    }

    // case two:
    lvl = 0;
    while (lvl < m)
    {
        lvl = borders[lvl];
        bmgoodskips[lvl-1] = min(bmgoodskips[lvl-1], lvl);
    }
}

//////////////////////////////////////////////////////////////////////////
}

char* naiive_search(char* haystack, int n, char* needle, int m)
{
    int pos = 0;
    int idx = 0;
    while (pos < n-m+1)
    {
        idx = 0;
        while (idx<m && haystack[pos+idx]==needle[idx]) { ++idx; }
        if (idx==m) { return &haystack[pos]; }
        ++pos;
    }
    return nullptr;
}

// bitap algorithm (also known as the shift-or, shift-and or Baeza–Yates–Gonnet algorithm)
char* bitap_bitwise_search(char* haystack, char* needle, int m)
{
    unsigned long R;
    unsigned long pattern_mask[CHAR_MAX+1];
    int i;

    if (needle[0] == '\0') return haystack;

    /* Initialize the bit array R */
    R = ~1;

    /* Initialize the pattern bitmasks */
    for (i=0; i <= CHAR_MAX; ++i)
        pattern_mask[i] = ~0;
    for (i=0; i < m; ++i)
        pattern_mask[needle[i]] &= ~(1UL << i);

    for (i=0; haystack[i] != '\0'; ++i) {
        /* Update the bit array */
        R |= pattern_mask[haystack[i]];
        R <<= 1;

        if (0 == (R & (1UL << m)))
            return (haystack + i - m) + 1;
    }

    return nullptr;
}

// assume m always larger than WORD_MAX
char* kmp_str_search(char* haystack, char* needle, int m)
{
    int start = 0;
    int index = 0;
    int *kmp_table;
    kmp_table = new int[m];
    get_kmp_table(kmp_table, needle, m);

    while (haystack[start+index] != '\0')
    {
        if (haystack[start+index] == needle[index])
        {
            if (index == m-1)
            {
                delete [] kmp_table;
                return &haystack[start];
            }
            ++index;
        } 
        else
        {
            start = start + index - kmp_table[index];
            index = max(0, kmp_table[index]);
        }
    }

    delete [] kmp_table;
    return nullptr;
}

char* BoyerMooreStrStr(char* str, int n, char* pat, int m)
{
    int bmbadskips[ALPHABET_SIZE];
    BmProcessBadSkips(bmbadskips, pat, m);

    int bmgoodskips[MAX_PATTERN_SIZE];
    BmProcessGoodSkips(bmgoodskips, pat, m);

    // search phase here:
    int pos = 0;
    int idx;
    while ( pos < (n-m+1) )
    {
        for (idx = m-1; idx >= 0 && pat[idx] == str[pos+idx]; --idx);

        if (idx < 0)
        {
            return &str[pos]; // return and terminate search
            // j += bmGs[0]; // keep going if need all matches
        }
        else
        {
            pos += max(bmgoodskips[idx], idx - bmbadskips[str[idx + pos]-CHAR_MIN]);
        }
    }
    
    return nullptr;
}