// Given a digit string, return all possible letter combinations that the number could represent.
//     A mapping of digit to letters (just like on the telephone buttons) is given below.
// ... 
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

class Solution {
private:
    void GenLetters(vector<string>& results, string& word, int idx, string& digits)
    {
        static const char* PHONE_LETTERS[] = {
            "0", "1", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        if(idx == (int)digits.size())
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

const std::string DEFAULT_INPUT_FILENAME = "default_input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    string inputFileName = DEFAULT_INPUT_FILENAME;
    string outputFilename = DEFAULT_OUTPUT_FILENAME;
    if (argc < 2)  {
        cout << "Usage: blah.exe filename.xxx" << endl;
    } else {
        inputFileName = argv[1];
        if (argc == 3) { outputFilename = argv[2]; }
    }

    // read input file and process along
    Solution solver;
    ifstream inFile(inputFileName.c_str(), ios::in);
    if (inFile.is_open()) {
        string digits;
        // Read in line by line
        while (getline(inFile, digits)) {
            vector<string> telewords = solver.letterCombinations(digits);
            cout << (*telewords.begin());
            for (size_t i=1; i<telewords.size(); ++i) {
                cout << ", " << telewords[i];
            }
            cout << endl;
        }

        inFile.close();
    }

    return 0;
}