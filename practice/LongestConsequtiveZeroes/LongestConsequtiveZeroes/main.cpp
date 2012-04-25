#include <iostream>

static const int BIT_DIGITS = sizeof(unsigned int) << 3;

int LeftCsZeroNum(unsigned int ix)
{
    int idx = BIT_DIGITS-1;
    while ((1<<idx & ix) == 0)
    {
        unsigned int y = 1<<idx;
        --idx;
    }
    return BIT_DIGITS-1-idx;
}

int RightCsZeroNum(unsigned int ix)
{
    int cnt = 0;
    while (ix != (ix | (1<<cnt)))
    {
        ++cnt;
    }
    return cnt;
}

int MaxCsZeroNum(unsigned int ix)
{
    int maxcnt = 0;
    int idx = 0;
    while (idx < BIT_DIGITS)
    {
        while (idx < BIT_DIGITS && (1<<idx & ix) != 0)
        {
            ++idx;
        }
        int cnt = 0;
        while (idx+cnt < BIT_DIGITS && (1<<idx & ix) == 0)
        {
            ++cnt;
        }
        if (cnt > maxcnt)
        {
            maxcnt = cnt;
        }
        idx = idx+cnt;
    }

    return maxcnt;
}

using namespace std;

int MaxConsecutiveZeroNum(unsigned int ary[], int length)
{
    int maxnum = 0;
    int num = 0;
    for (int i=0; i<length; ++i)
    {
        if (ary[i] == 0)
        {
            num+=32;
        } 
        else
        {
            num += LeftCsZeroNum(ary[i]);
            num = max(num, MaxCsZeroNum(ary[i]));
            if (num > maxnum) maxnum = num;

            num = RightCsZeroNum(ary[i]);
        }
    }

    return maxnum;
}

int main(int argc, char** argv)
{
    const int ARRYSIZE = 4;
    unsigned int ary[ARRYSIZE];
    ary[0] = 1<<31;
    for (int i=1; i<ARRYSIZE; ++i)
    {
        ary[i] = i;
    }

    int num = MaxConsecutiveZeroNum(ary, ARRYSIZE);

    return 0;
}