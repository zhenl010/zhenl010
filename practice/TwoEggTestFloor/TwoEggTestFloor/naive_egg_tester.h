#ifndef NAIVE_EGG_TESTER_H
#define NAIVE_EGG_TESTER_H

#include "egg_tester.h"

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

class NaiveEggTester : public EggTester
{
public:
    NaiveEggTester(int maxlvl, int eggnum);
    ~NaiveEggTester();

    int BreakLevel(int minlvl, int lvl_num, int egg_num, const TestEgg& eggtype);

private:
    void Init();

    int** required_attempts;
};

//////////////////////////////////////////////////////////////////////////
}

#endif