#include <iostream>
#include <string>
#include "boyer_moore_strstr.h"

namespace { // unnamed namespace
//////////////////////////////////////////////////////////////////////////

// short patterns naiive_search ONLY
static const int WORD_MAX = 4;

const char* NaiiveStringFind(const char* haystack, int n, const char* needle, int m) {
    int pos = 0;
    int idx = 0;
    while (pos < n-m+1) {
        idx = 0;
        while (idx<m && haystack[pos+idx]==needle[idx]) { ++idx; }
        if (idx==m) { return &haystack[pos]; }
        ++pos;
    }
    return NULL;
}

void GetKmpTable(int* kmp_table, const char* needle, int m) {
    kmp_table[0] = -1;
    kmp_table[1] = 0;

    int pos = 2;
    int cnd = 0;

    while (pos < m) {
        if (needle[pos-1] == needle[cnd]) {
            ++cnd;
            kmp_table[pos] = cnd;
            ++pos;
        } else if (cnd > 0) {
            cnd = kmp_table[cnd];
        } else {
            kmp_table[pos++] = 0;
        }
    }
}

// assume m always larger than WORD_MAX
const char* KmpStringFind(const char* haystack, const char* needle, int m) {
    int start = 0;
    int index = 0;
    int *kmp_table;
    kmp_table = new int[m];
    GetKmpTable(kmp_table, needle, m);

    while (haystack[start+index] != '\0') {
        if (haystack[start+index] == needle[index]) {
            if (index == m-1) {
                delete [] kmp_table;
                return &haystack[start];
            }
            ++index;
        } else {
            start = start + index - kmp_table[index];
            index = std::max(0, kmp_table[index]);
        }
    }

    delete [] kmp_table;
    return NULL;
}

//////////////////////////////////////////////////////////////////////////
}
// Locate substring
// Returns a pointer to the first occurrence of needle in haystack,
// or a null pointer if needle is not part of haystack.
const char* FindSubstr(const char *haystack, const char *needle) {
    int m = strlen(needle);
    if (m == 0) return haystack; // by default!!!

    if (m > WORD_MAX) {
        return BoyerMooreStrStr(haystack, strlen(haystack), needle, m);
        // return KmpStringFind(haystack, needle, m);
    } else {
        return NaiiveStringFind(haystack, strlen(haystack), needle, m);
    }

}

int main(int argc, char** argv) {
    char str[] ="This is a simple string";

    puts (str);
    puts (strstr (str,"simple"));
    puts (FindSubstr (str,"simple"));

    return 0;
}