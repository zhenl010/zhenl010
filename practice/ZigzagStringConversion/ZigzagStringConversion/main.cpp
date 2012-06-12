#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// precondition nRows>1 !!!
class ZigzagConverter {
public:
    ZigzagConverter(const string& s, int nRows);
    string ZigzagString();

private:
    string ZigzagConvertExact();
    string ZigzagConvertOne();
    string ZigzagConvertTwo();

    const string& text_;
    const int nRows_;
    const int strsize_; // = text.size();
    const int L_; // = nRows + nRows - 1;
    const int nl_; // = strsize / L;
    const int nres_; // = strsize % L;
};

ZigzagConverter::ZigzagConverter(const string& s, int nRows)
: text_(s), nRows_(nRows), strsize_(s.size()),
L_(nRows+nRows-2), nl_(strsize_/L_), nres_(strsize_%L_) {
}

string ZigzagConverter::ZigzagString() {
    if (nres_ == 0) {
        return ZigzagConvertExact();
    } else if (nres_ < nRows_) {
        return ZigzagConvertOne();
    } else {
        return ZigzagConvertTwo();
    }
}

string ZigzagConverter::ZigzagConvertExact() {
    string str(strsize_, '\0');
    int newidx = 0;
    int oldidx = 0;
    // 1st row:
    for (int iz=0; iz<nl_; ++iz) {
        str[newidx++] = text_[oldidx];
        oldidx += L_;
    }

    // 2nd till the row before double tail:
    for (int row=1; row<(nRows_-1); ++row) {
        int lfi = row;
        int rti = L_-row;
        for (int iz=0; iz<nl_; ++iz) {
            str[newidx] = text_[lfi];
            str[newidx+1] = text_[rti];
            lfi += L_;
            rti += L_;
            newidx += 2;
        }
    }
    // last row:
    int orindx = nRows_-1;
    for (int iz=0; iz<nl_; ++iz) {
        str[newidx++] = text_[orindx];
        orindx += L_;
    }
    return str;
}

string ZigzagConverter::ZigzagConvertOne() {
    string str(strsize_, '\0');
    int newidx = 0;
    int oldidx = 0;
    // 1st row:
    for (int iz=0; iz<nl_+1; ++iz) {
        str[newidx++] = text_[oldidx];
        oldidx += L_;
    }

    // 2nd till the nres_'s row has one extra:
    for (int row=1; row<nres_; ++row) {
        int lfi = row;
        int rti = L_-row;
        for (int iz=0; iz<nl_; ++iz) {
            str[newidx] = text_[lfi];
            str[newidx+1] = text_[rti];
            lfi += L_;
            rti += L_;
            newidx += 2;
        }
        // one extra element each row
        str[newidx++] = text_[lfi];
    }
    // 2nd till the row before double tail:
    for (int row=nres_; row<(nRows_-1); ++row) {
        int lfi = row;
        int rti = L_-row;
        for (int iz=0; iz<nl_; ++iz) {
            str[newidx] = text_[lfi];
            str[newidx+1] = text_[rti];
            lfi += L_;
            rti += L_;
            newidx += 2;
        }
    }
    // last row:
    int orindx = nRows_-1;
    for (int iz=0; iz<nl_; ++iz) {
        str[newidx++] = text_[orindx];
        orindx += L_;
    }
    return str;
}

string ZigzagConverter::ZigzagConvertTwo() {
    string str(strsize_, '\0');
    int newidx = 0;
    int oldidx = 0;
    // 1st row:
    for (int iz=0; iz<nl_+1; ++iz) {
        str[newidx++] = text_[oldidx];
        oldidx += L_;
    }

    int neone = (nRows_-1)+nRows_-nres_;
    // 2nd till the row before double tail:
    for (int row=1; row<neone; ++row) {
        int lfi = row;
        int rti = L_-row;
        for (int iz=0; iz<nl_; ++iz) {
            str[newidx] = text_[lfi];
            str[newidx+1] = text_[rti];
            lfi += L_;
            rti += L_;
            newidx += 2;
        }
        // one extra element each row
        str[newidx++] = text_[lfi];
    }
    // double tail rows till the row before the last row:
    for (int row=neone; row<(nRows_-1); ++row) {
        int lfi = row;
        int rti = L_-row;
        for (int iz=0; iz<nl_+1; ++iz) {
            str[newidx] = text_[lfi];
            str[newidx+1] = text_[rti];
            lfi += L_;
            rti += L_;
            newidx += 2;
        }
    }
    // last row:
    int orindx = nRows_-1;
    for (int iz=0; iz<nl_+1; ++iz) {
        str[newidx++] = text_[orindx];
        orindx += L_;
    }
    return str;
}

class Solution {
public:
    string convert(string s, int nRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (nRows < 2) return s;
        ZigzagConverter helper(s, nRows);
        return helper.ZigzagString();
    }
};

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const std::string DEFAULT_INPUT_FILENAME = "default_input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    string inputFileName = DEFAULT_INPUT_FILENAME;
    string outputFilename = DEFAULT_OUTPUT_FILENAME;
    if (argc < 2)  {
        cout << "Usage: blah.exe filename.xxx" << endl;
    } else {
        inputFileName = argv[1];
        if (argc == 3) { outputFilename = argv[2]; }
    }
    cout << "importing from FILE:   " << inputFileName  << endl;
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl;

    Solution solver;

    // read input file and process along
    ifstream inFile(inputFileName, ios::in);
    if (inFile.is_open()) {
        string line_str;
        // Read in line by line
        while (getline(inFile, line_str)) {
            stringstream line_stream(line_str);
            string text;
            line_stream >> text;
            int rownum;
            line_stream >> rownum;
            string expectedstr;
            line_stream >> expectedstr;

            string zigzagstr = solver.convert(text, rownum);
            if (zigzagstr != expectedstr) { // wrong restult!
                cout << endl << "WRONG RESULT: " << endl;
            }
        }

        inFile.close();
    }

    return 0;
}