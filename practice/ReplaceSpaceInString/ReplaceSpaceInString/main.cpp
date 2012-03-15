#include <iostream>
#include <string>

void ReplaceSpaceInString(std::string& str)
{
    int length = str.size();
    int wnum = 0;
    for (int i=0; i<length; ++i)
    {
        if (str[i] == ' ')
        {
            ++wnum;
        }
    }

    str.resize(length+wnum*2);
    for (int i=length-1, j=str.size()-1; i>=0; --i, --j)
    {
        if (str[i]==' ')
        {
            str[j--]='0';
            str[j--]='2';
            str[j]='%';
        } 
        else
        {
            str[j] = str[i];
        }
    }
}

int main()
{
    std::string str = "John Carter is a bad movie! ";
    std::cout << str << std::endl;
    ReplaceSpaceInString(str);
    std::cout << str << std::endl;

    return 0;
}