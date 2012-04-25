#ifndef STRING_SEARCH_H_
#define STRING_SEARCH_H_

// short patterns naiive_search ONLY
static const int WORD_MAX = 4;

// Assume array sizes are real size (not including trailing '\0')
char* naiive_search(char* haystack, int n, char* needle, int m);
char* bitap_bitwise_search(char* haystack, char* needle, int m); // Bitap (Shift-Or)
char* kmp_str_search(char* haystack, char* needle, int m); // Knuth-Morris-Pratt
char* BoyerMooreStrStr(char* str, int n, char* pat, int m);  // Boyer-Moore

#endif