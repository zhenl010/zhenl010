#ifndef BETTER_EGG_TESTER_H_
#define BETTER_EGG_TESTER_H_

#include "egg_tester.h"

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

class BetterEggTester : public EggTester
{
public:
    BetterEggTester(int maxlvl, int eggnum);
    ~BetterEggTester();

    int RequiredAttempts(int egg_num, int atnum);
    int BreakLevel(int minlvl, int lvl_num, int egg_num, const TestEgg& eggtype);

private:
    void Init();
    int CoveredLevel(int egg_num, int atnum);

    int max_attempts_;
    int** covered_levels_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif