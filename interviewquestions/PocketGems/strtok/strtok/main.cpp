// Split string into tokens
// A sequence of calls to this function split str into tokens, which are sequences of contiguous characters separated by any of the characters that are part of delimiters.
// On a first call, the function expects a C string as argument for str, whose first character is used as the starting location to scan for tokens. In subsequent calls, the function expects a null pointer and uses the position right after the end of last token as the new starting location for scanning.
// To determine the beginning and the end of a token, the function first scans from the starting location for the first character not contained in delimiters (which becomes the beginning of the token). And then scans starting from this beginning of the token for the first character contained in delimiters, which becomes the end of the token.
// This end of the token is automatically replaced by a null-character by the function, and the beginning of the token is returned by the function.
// Once the terminating null character of str has been found in a call to strtok, all subsequent calls to this function with a null pointer as the first argument return a null pointer.
// The point where the last token was found is kept internally by the function to be used on the next call (particular library implementations are not required to avoid data races).
// 
// Parameters
// str
// C string to truncate.
// Notice that the contents of this string are modified and broken into smaller strings (tokens).
// Alternativelly, a null pointer may be specified, in which case the function continues scanning where a previous successful call to the function ended.
// delimiters
// C string containing the delimiter characters.
// These may vary from one call to another.
#include <iostream>
#include <cstring>

bool IsDelim(char* p, const char* delim);
char* CstrTok(char* str, const char* delim);
// with restrict(or __restrict) optimization:
//char* CstrTok(char* __restrict str, const char* delim);

// regular version:
char* CstrTok(char* str, const char* delim) {
    static char* buffer = NULL;
    char* curr = (str==NULL) ? buffer : str;
    if (curr == NULL) return NULL; // early return if no string at all

    while (IsDelim(curr, delim)) { ++curr; }
    buffer = curr;
    while (!IsDelim(buffer, delim)) { ++buffer; }
    buffer = ((*buffer) != '\0') ? *buffer='\0',++buffer : NULL;
    return curr;
}

bool IsDelim(char* p, const char* delim) {
    if (p==NULL || delim==NULL) return false; // defined as is
    for (const char* q=delim; *q != '\0'; ++q) {
        if (*p == *q) return true;
    }
    return false;
}

int main() {
    // Using a string literal to initialize a char * pointer in C++ is
    // a deprecated feature, but nevertheless it is legal. It is not an error.
    // It is your responsibility to make sure that no modification attempts are made through such a pointer.
    char *p1="hello";
    char *p2="hello";    
    // *p1='m'; // string literals are constants and cant be modified
    if (p1 == p2) { // both pointing to the same const c_string
        printf("%s; %s\n", p1, p2);
    }

    // Here, the compiler will count the number of characters within the string, 
    // will create the string_ array based on the size of the string, 
    // and will populate the array with the characters of the string.
    char chstr[] = "hello";
    if (chstr != p1) { // different way of declaration cause differences!!!
        printf("%s; %s; and %s.\n", p1, p2, chstr);        
    }


    //////////////////////////////////////////////////////////////////////////

        
    char* delims = ", .-;";
    char str_one[] = "- This, a sample string.";
    char str_two[] = "- This, a sample string.";
    printf("Splitting string \"%s\" into tokens using strtok:\n", str_one);
    printf("Splitting string \"%s\" into tokens using CstrTok:\n", str_two);
    char* pch_one = strtok(str_one, delims);
    char* pch_two = CstrTok(str_two, delims);
    while (pch_one != NULL) {
        if (strcmp(pch_one, pch_two) != 0) {
            printf("WRONG RESULT!!!\n");
        }
        printf("%s\n", pch_one);
        pch_one = strtok(NULL, delims);
        pch_two = CstrTok(NULL, delims);
    }

    return 0;
}