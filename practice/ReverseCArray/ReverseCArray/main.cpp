#include <iostream>

void ReverseArray(char *str)
{
    int length = 0;
    for (; str[length] != '\0'; ++length);
    --length;

    int half = length >> 1;
    for (int i=0; i<=half; ++i)
    {
        std::swap(str[i], str[length-i]);
    }
}

int main()
{
    char test_str[] = "abccde";

    std::cout << "original string: " << test_str << std::endl;
    std::cout << "reversed to: " << std::endl;
    ReverseArray(test_str);
    std::cout << "original string: " << test_str << std::endl;

    return 0;
}