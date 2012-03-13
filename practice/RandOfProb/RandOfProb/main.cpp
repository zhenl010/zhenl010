// 给你一个函数 bool Prob() ，有50%的概率返回 True，50%的概率返回 
//     False
//     请你用写一个新的函数：bool Prob2(double p)
//     要求  p 的概率返回 True， 1 - p 的概率返回 False
#include <iostream>

bool RandBinary()
{
    return rand() % 2 == 0;
}

bool RandBinary(double p)
{
    if (p>0.5)
    {
        return !RandBinary(1.0-p);
    } 
    else
    {
        if (RandBinary() == false)
        {
            return false;
        } 
        else
        {
            return RandBinary(2.0*p);
        }
    }
}

int main()
{
    double p = 1.0 / 3.0;
    int test_count = 3 * (INT_MAX / 128);

    int counts[2];
    counts[0]=0;
    counts[1]=0;
    for (int i=0; i<test_count; ++i)
    {
        if (RandBinary(p) == false)
        {
            ++counts[0];
        } 
        else
        {
            ++counts[1];
        }
    }

    std::cout << p << std::endl;
    std::cout << double(counts[1]) / test_count << std::endl;

    return 0;
}