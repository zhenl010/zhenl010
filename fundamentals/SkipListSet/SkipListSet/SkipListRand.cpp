#include "SkipListRand.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

namespace // local variables
{
    // the eighth Mersenne prime, 2**31−1
    const int LCG_PRIME_M = 2147483647;
    const int LCG_CONST_A = 16807;
    const int LCG_CONST_Q = LCG_PRIME_M / LCG_CONST_A;
    const int LCG_CONST_R = LCG_PRIME_M % LCG_CONST_A;
    int randSeed = 1;
}

int SkipListRand()
{
    randSeed = LCG_CONST_A * (randSeed % LCG_CONST_Q) - LCG_CONST_R * (randSeed / LCG_CONST_Q);

    if (randSeed < 0)
    {
        randSeed += LCG_PRIME_M;
    }

    return randSeed;
}

void SetSkipListRandSeed(int newSeed)
{
    randSeed = newSeed;
}

int SkipListRandMax()
{
    return LCG_PRIME_M;
}

//////////////////////////////////////////////////////////////////////////
}
