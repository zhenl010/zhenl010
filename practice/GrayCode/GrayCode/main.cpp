#include <iostream>
#include <string>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;

void GrayCodeRe(string& word, int idx, int n)
{
    if (idx == n)
    {
        cout << word << endl;
        return;
    }

    GrayCodeRe(word, idx+1, n);
    word[idx] = '0' + '1' - word[idx];
    GrayCodeRe(word, idx+1, n);
}

void GrayCode(int n)
{
    string word(n, '0');
    GrayCodeRe(word, 0, n);
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv)
{
    int num = 4;

    GrayCode(num);

    return 0;
}