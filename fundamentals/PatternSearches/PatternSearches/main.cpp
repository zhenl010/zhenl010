// PATTERN search (substring only) as generalized string searchings
// notice no code optimization yet ...
// ref: http://www-igm.univ-mlv.fr/~lecroq/string/node1.html
#include <iostream>
#include "kmp_search.h"

template<typename T, int N>
int ArraySize(T (&) [N]) { return N; }

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = strlen(haystack);
        int m = strlen(needle);
        if(m==0) return haystack;

        return KmpSearch(haystack, n, needle, m);
    }

private:
    char* KmpSearch(char* text, int n, char* pattern, int m) {
        BuildKmpTable(pattern, m);

        int i=0;
        int j=0;
        while(j<n) {
            while(i>=0 && text[j]!=pattern[i]) i=kmp_next_[i];

            ++i; ++j;
            if(i==m) return &(text[j-i]); // match found
        }

        return NULL; // no match
    }

    void BuildKmpTable(char* pat, int m) {
        kmp_next_[0] = -1;
        int border = -1;
        for (int i=1; i<m; ++i) {
            while(border>=0 && pat[border]!=pat[i-1]) border=kmp_next_[border];
            ++border;
            if(pat[i]!=pat[border]) {
                kmp_next_[i] = border;
            } else {
                kmp_next_[i] = kmp_next_[border];
            }
        }
    }

    static const int BUFFER_SIZE = 1 << 16; /// @TODO: change to dynamic array or not?
    int kmp_next_[BUFFER_SIZE];
};

int main() {
    // any primitive object (without pointer) saved as consecutive chunk of memory,
    // thus can be think of an array of word (char)

    using namespace std;

    Solution solver;
    char* outstr = solver.strStr("mississippi", "issi");

    char text[] = "abacabac abac abaabacabacabacadf\n"
        "Contents\n"
        "Introduction\n"
        "\tFrom left to right\n"
        "\tFrom right to left\n"
        "\tIn a specific order\n"
        "\tIn any order\n"
        "Definitions\n"
        "Implementation\n"
        "Brute Force algorithm\n"
        "Deterministic Finite Automaton algorithm\n"
        "Karp-Rabin algorithm\n"
        "Shift Or algorithm\n"
        "Morris-Pratt algorithm\n"
        "Knuth-Morris-Pratt algorithm\n"
        "Simon algorithm\n"
        "Colussi algorithm\n"
        "Galil-Giancarlo algorithm\n"
        "Apostolico-Crochemore algorithm\n"
        "Not So Naive algorithm\n"
        "Boyer-Moore algorithm\n"
        "Turbo BM algorithm\n"
        "Apostolico-Giancarlo algorithm\n"
        "Reverse Colussi algorithm\n"
        "Horspool algorithm\n"
        "Quick Search algorithm\n"
        "Tuned Boyer-Moore algorithm\n"
        "Zhu-Takaoka algorithm\n"
        "Berry-Ravindran algorithm\n"
        "Smith algorithm\n"
        "Raita algorithm\n"
        "Reverse Factor algorithm\n"
        "Turbo Reverse Factor algorithm\n"
        "Forward Dawg Matching algorithm\n"
        "Backward Nondeterministic Dawg Matching algorithm\n"
        "Backward Oracle Matching algorithm\n"
        "Galil-Seiferas algorithm\n"
        "Two Way algorithm\n"
        "String Matching on Ordered Alphabets algorithm\n"
        "Optimal Mismatch algorithm\n"
        "Maximal Shift algorithm\n"
        "Skip Search algorithm\n"
        "KMP Skip Search algorithm\n"
        "Alpha Skip Search algorithm\n"
        "Postscript\n"
        "Portable Document Format\n"
        "e-mails: {Christian.Charras, Thierry.Lecroq}@laposte.net\n"
        "Tue Jan 14 15:03:31 MET 1997\n";

    cout << text << endl << endl;

    char pattern[] = "abacabacaba";

    cout << pattern << endl << endl;

    int pos = KmpSearch(text, ArraySize(text)-1, pattern, ArraySize(pattern)-1); // !!! notice "-1"

    cout << "Find pattern at position: " << pos << endl;

    return 0;
}