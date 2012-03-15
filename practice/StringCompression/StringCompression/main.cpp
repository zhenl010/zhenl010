#include <iostream>
#include <string>
#include <sstream>

void CompressString(std::string& str)
{
    using namespace std;
    if (str.empty())
    {
        return;
    }

    char prev = str[0];
    int count = 1;
    stringstream strm;
    for (int i=1; i<static_cast<int>(str.size()); ++i)
    {
        if (str[i] != prev)
        {
            strm << prev << count;
            prev = str[i];
            count = 1;
        } 
        else
        {
            ++count;
        }
    }
    strm << prev << count;
    if (strm.str().size() < str.size())
    {
        str = strm.str();
    }
}

int main()
{
    using namespace std;
    string str = "abcd2";
    cout << str << endl;
    CompressString(str);
    cout << str << endl;

    return 0;
}