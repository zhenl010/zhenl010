#include "kmp_search.h"
#include <climits>

namespace {
//////////////////////////////////////////////////////////////////////////

const int BUFFER_SIZE = 1 << 16; /// @TODO: change to dynamic array or not?

int kmp_buffer[BUFFER_SIZE];  /// global buffer in anonymous namespace

// pre-condition: m >= 1
void BuildKmpTable(char pat[], int m, int nexts[]) {
    nexts[0] = -1;
    int border = nexts[0];

    // MP algorithm uses normal border
    // for (int i=0; i<m; ++i) {
    //     while(border>=0 && pat[border]!=pat[i]) border=nexts[border];
    //     nexts[i+1] = ++border;
    // }

    // KMP algorithm uses strict border
    for(int i=0; i<m-1; ++i) {
        while(border>=0 && pat[border]!=pat[i]) border=nexts[border];
        ++border;
        if(pat[border] != pat[i+1]) {
            nexts[i+1] = border;
        } else {
            nexts[i+1] = nexts[border];
        }
    }
    nexts[m] = border;
}

int KmpSearch(char text[], int n, char pattern[], int m, int kmp_next[]) {
    BuildKmpTable(pattern, m, kmp_next);

    int i = 0;
    int j = 0;
    while(j<n) {
        while(i==m || (i>=0 && pattern[i]!=text[j])) i=kmp_next[i];

        ++j; ++i;
        if(i==m) return j-i; // or output pos and keep going
    }

    return n; // which is always a valid fail position
}

//////////////////////////////////////////////////////////////////////////
}

int KmpSearch(char text[], int n, char pattern[], int m) {
    return KmpSearch(text, n, pattern, m, kmp_buffer);
}