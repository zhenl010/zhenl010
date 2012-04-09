//////////////////////////////////////////////////////////////////////////
// F(n,m)=1+min_x( max(F(x-1,m-1), F(n-x,m)) )
// Linear search to find x
//////////////////////////////////////////////////////////////////////////
#include "naive_egg_tester.h"
#include <cassert>
#include <climits>
#include <algorithm>
#include "test_egg_class.h"

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

NaiveEggTester::NaiveEggTester(int maxlvl, int eggnum)
    : EggTester(maxlvl, eggnum)
{
    // Allocate done at construction
    required_attempts = new int*[MAX_LVL_+1]; // floor to max level
    for (int i=0; i<=MAX_LVL_; ++i)
    {
        required_attempts[i] = new int[MAX_EGG_NUM_+1] ();
    }

    Init();
}

NaiveEggTester::~NaiveEggTester()
{
    for (int i=0; i<=MAX_LVL_; ++i)
    {
        delete[] required_attempts[i];
    }
    delete[] required_attempts;
}

int NaiveEggTester::BreakLevel(int minlvl, int lvl_num, int egg_num, const TestEgg& eggtype)
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

    int lvl_diff = required_attempts[lvl_num][egg_num];
    int next_lvl = minlvl + lvl_diff - 1;
    if (eggtype.EggBreak(next_lvl))
    {
        return BreakLevel(minlvl, lvl_diff-1, egg_num-1, eggtype);
    } 
    else
    {
        return BreakLevel(next_lvl+1, lvl_num-lvl_diff, egg_num, eggtype);
    }
}

// Notice allocation is done at construction
void NaiveEggTester::Init()
{
    // Init values. Note floor level starts from one
    for (int lvl=1; lvl<=MAX_LVL_; ++lvl)
    {
        required_attempts[lvl][1] = lvl;
    }

    for (int num=2; num<=MAX_EGG_NUM_; ++num)
    {
        required_attempts[1][num] = 1;
        for (int lvl=2; lvl<=MAX_LVL_; ++lvl)
        {
            // Central comparison here:
            int att_num = INT_MAX;
            for (int atlvl=1; atlvl<lvl; ++atlvl)
            {
                int curr_num = std::max(required_attempts[atlvl-1][num-1], required_attempts[lvl-atlvl][num]);
                if (curr_num < att_num)
                {
                    att_num = curr_num;
                }
            }
            required_attempts[lvl][num] = att_num + 1;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
}