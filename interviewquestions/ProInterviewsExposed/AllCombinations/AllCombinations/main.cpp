#include <iostream>
#include <string>

namespace {
//////////////////////////////////////////////////////////////////////////

using namespace std;

void PrintAllCombinations(string& str, string& cmb, int idx) {
    cout << cmb << endl;
    for(int i=idx; i<str.size(); ++i) {
        cmb += str[i];
        PrintAllCombinations(str, cmb, i+1);
        cmb.resize(cmb.size()-1);
    }
}

// assume no duplicates
void PrintAllCombinations(string str) {
    string cmb;
    PrintAllCombinations(str, cmb, 0);
}

//////////////////////////////////////////////////////////////////////////
}

int main() {
    string str = "wxyz";

    PrintAllCombinations(str);

    return 0;
}