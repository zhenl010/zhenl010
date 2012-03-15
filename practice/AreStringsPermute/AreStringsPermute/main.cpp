#include <iostream>
#include <string>
#include <unordered_map>

bool IsPermute(std::string str_one, std::string str_two)
{
    using namespace std;

    if (str_one.size() != str_two.size())
    {
        return false;
    }

    unordered_map<char, int> m1, m2;
    for (int i=0; i<str_one.size(); ++i)
    {
        m1[str_one[i]]++;
        m2[str_two[i]]++;
    }

    if (m1.size() != m2.size())
    {
        return false;
    }

    for (unordered_map<char, int>::iterator it=m1.begin(); it!=m1.end(); ++it)
    {
        if (m2[(*it).first] != it->second)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    using namespace std;

    string str_one = "abca";
    string str_two = "cbaa";

    cout << str_one << endl;
    cout << str_two << endl;
    if (IsPermute(str_one, str_two))
    {
        cout << "PERMUTE" << endl;
    } 
    else
    {
        cout << "NOT PERMUTE" << endl;
    }

    return 0;
}