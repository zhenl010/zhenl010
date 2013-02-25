#include "boyer_moore_strstr.h"
#include <climits>

namespace {
//////////////////////////////////////////////////////////////////////////

// Assume array sizes are real size (not including trailing '\0')
const int ALPHABET_SIZE = CHAR_MAX-CHAR_MIN+1;
const int MAX_PATTERN_SIZE = 1<<16;

inline char max ( char a, char b ) {
    return (a<b) ? b:a;
}

inline char min ( char a, char b ) {
    return (a<b) ? a:b;
}

void BmProcessBadSkips(int* badcharskips, const char* pat, int m) {
    int i;
    for (i=0; i<ALPHABET_SIZE; ++i) {
        badcharskips[i] = -1;
    }

    for (i=0; i<m; ++i) {
        badcharskips[pat[i]-CHAR_MIN] = i;
    }
}

void ProcessBorders(int* border, const char* x, int m) {
    border[m-1] = m;
    for (int i=m-2; i>=0; --i) {
        int lvl = i+1;
        while ((lvl < m) && (x[i] != x[border[lvl]-1])) {
            lvl = border[lvl];
        }

        if (lvl == m) { // no border
            border[i] = m;
        } else {
            border[i] = border[lvl]-1;
        }
    }
}

void BmProcessGoodSkips(int* bmgoodskips, const char* pat, int m) {
    int borders[MAX_PATTERN_SIZE+1];
    ProcessBorders(borders, pat, m);

    int idx;
    int lvl;
    bmgoodskips[m-1] = 1; // Init
    for (idx=0; idx<m-1; ++idx) {
        bmgoodskips[idx] = borders[0];
    }

    // case one:
    for (idx=0; idx<m-1; ++idx) {
        lvl = idx+1;
        lvl = borders[lvl];
        while (lvl < m && pat[idx] != pat[lvl-1]) {
            bmgoodskips[lvl-1] = lvl - idx - 1;
            lvl = borders[lvl];
        }
    }

    // case two:
    lvl = 0;
    while (lvl < m) {
        lvl = borders[lvl];
        bmgoodskips[lvl-1] = min(bmgoodskips[lvl-1], lvl);
    }
}

//////////////////////////////////////////////////////////////////////////
}

const char* BoyerMooreStrStr(const char* str, int n, const char* pat, int m) {
    int bmbadskips[ALPHABET_SIZE];
    BmProcessBadSkips(bmbadskips, pat, m);

    int bmgoodskips[MAX_PATTERN_SIZE];
    BmProcessGoodSkips(bmgoodskips, pat, m);

    // search phase here:
    int pos = 0;
    int idx;
    while ( pos < (n-m+1) ) {
        for (idx = m-1; idx >= 0 && pat[idx] == str[pos+idx]; --idx);

        if (idx < 0) {
            return &str[pos]; // return and terminate search
            // j += bmGs[0]; // keep going if need all matches
        } else {
            pos += max(bmgoodskips[idx], idx - bmbadskips[str[idx + pos]-CHAR_MIN]);
        }
    }

    return nullptr;
}