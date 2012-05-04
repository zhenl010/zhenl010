// Given a digit string, return all possible letter combinations that the number could represent.
//     A mapping of digit to letters (just like on the telephone buttons) is given below.
// ... 
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void GenLetters(vector<string>& results, string& word, int idx, string& digits)
    {
        static const char* PHONE_LETTERS[] = {
            " ", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        if(idx == digits.size())
        {
            results.push_back(word);
            return;            
        }

        const char* ch = PHONE_LETTERS[digits[idx]-'0'];
        while(ch!=NULL && *ch!='\0')
        {
            word[idx] = *ch;
            GenLetters(results, word, idx+1, digits);
            ++ch;
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        vector<string> results;
        string word(digits.size(), '\0');
        GenLetters(results, word, 0, digits);
        return results;
    }
};

int main(int argc, char** argv)
{
    return 0;
}