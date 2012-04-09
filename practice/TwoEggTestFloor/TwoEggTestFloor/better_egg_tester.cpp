//////////////////////////////////////////////////////////////////////////
// N(m,t) = N(m-1,t-1)+1+N(m,t-1)
// binary search to find N
//////////////////////////////////////////////////////////////////////////
#include "better_egg_tester.h"
#include <cassert>
#include <climits>
#include <algorithm>
#include "test_egg_class.h"

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

BetterEggTester::BetterEggTester(int maxlvl, int eggnum)
    : EggTester(maxlvl, eggnum)
{
    // max number of attempts to fully examine all levels
    max_attempts_ = MAX_LVL_; // when eggnum is ONE
    // Allocate done at construction
    covered_levels_ = new int*[MAX_EGG_NUM_+1]; // floor to max level
    for (int i=0; i<=MAX_EGG_NUM_; ++i)
    {
        covered_levels_[i] = new int[max_attempts_+1] ();
    }

    Init();
}

BetterEggTester::~BetterEggTester()
{
    for (int i=0; i<=MAX_EGG_NUM_; ++i)
    {
        delete[] covered_levels_[i];
    }
    delete[] covered_levels_;
}

int BetterEggTester::RequiredAttempts(int egg_num, int maxlvl)
{
    int lf_att = 1;
    int rt_att = maxlvl;

    int ct_att;
    while ( !(rt_att<lf_att) )
    {
        ct_att = lf_att + (rt_att-lf_att)/2;
        if (maxlvl < CoveredLevel(egg_num, ct_att))
        {
            rt_att = ct_att - 1;
        } 
        else
        {
            lf_att = ct_att + 1;
        }
    }

    return ct_att;
}

int BetterEggTester::BreakLevel(int minlvl, int lvl_num, int egg_num, const TestEgg& eggtype)
{
    assert(egg_num>0 && minlvl>0);

    if (lvl_num < 1)
    {
        return minlvl;
    }

    if (egg_num == 1) // only egg test cautiously
    {
        int brklvl = minlvl;
        while ((brklvl-minlvl<lvl_num) && (eggtype.EggBreak(brklvl)==false))
        {
            ++brklvl;
        }
        return brklvl;
    }

    int req_at = RequiredAttempts(egg_num, lvl_num);
    int next_lvl = minlvl + req_at - 1;
    if (eggtype.EggBreak(next_lvl))
    {
        return BreakLevel(minlvl, req_at-1, egg_num-1, eggtype);
    } 
    else
    {
        return BreakLevel(next_lvl+1, lvl_num-req_at, egg_num, eggtype);
    }
}

// Notice allocation is done at construction
void BetterEggTester::Init()
{
    // Init values. Note floor level starts from one
    for (int lvl=1; lvl<=MAX_LVL_; ++lvl)
    {
        covered_levels_[1][lvl] = lvl;
    }

    for (int num=2; num<=MAX_EGG_NUM_; ++num)
    {
        covered_levels_[num][1] = 1;
        for (int attempt=2; attempt<=max_attempts_; ++attempt)
        {
            covered_levels_[num][attempt] = covered_levels_[num-1][attempt-1] + 1 + covered_levels_[num][attempt-1];
        }
    }
}

int BetterEggTester::CoveredLevel(int egg_num, int atnum)
{
    return covered_levels_[egg_num][atnum];
}

//////////////////////////////////////////////////////////////////////////
}