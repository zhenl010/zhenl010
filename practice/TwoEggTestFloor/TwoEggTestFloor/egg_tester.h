//////////////////////////////////////////////////////////////////////////
// Find the threshold+1 level given test scene
// Assume the start scene provide enough info.
//////////////////////////////////////////////////////////////////////////
#ifndef EGG_TESTER_H_
#define EGG_TESTER_H_

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

class TestEgg;
class EggTester
{
public:
    EggTester(int maxlvl, int eggnum) : MAX_LVL_(maxlvl), MAX_EGG_NUM_(eggnum) {}

    virtual int BreakLevel(int minlvl, int lvl_num, int egg_num, const TestEgg& eggtype) = 0;

protected:
    const int MAX_LVL_;
    const int MAX_EGG_NUM_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif