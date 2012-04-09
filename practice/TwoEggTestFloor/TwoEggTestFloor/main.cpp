// You are given 2 eggs.
// You have access to a 100-storey building.
// Eggs can be very hard or very fragile means it may break 
// if dropped from the first floor or may not even break if dropped from 100 th floor.Both eggs are identical.
// You need to figure out the highest floor of a 100-storey building an egg can be dropped without breaking.
// Now the question is how many drops you need to make. You are allowed to break 2 eggs in the process
#include <cassert>
#include <iostream>
#include "test_egg_class.h"
#include "naive_egg_tester.h"
#include "better_egg_tester.h"

namespace // unnamed namespace
{
    const int MAX_LEVEL = 100;
    const int MAX_EGG_NUM = 2;
}

int main(int argc, char** argv)
{
    using namespace std;
    using namespace aug_puzzle_lib;

    // Prepare some eggs @@
    TestEgg eggs[MAX_LEVEL];
    for (int i=0; i<MAX_LEVEL; ++i)
    {
        eggs[i].Reset(i);
    }

    NaiveEggTester naivetester(MAX_LEVEL, MAX_EGG_NUM);
    BetterEggTester bettertester(MAX_LEVEL, MAX_EGG_NUM);

    EggTester* testers[2];

    testers[0] = &naivetester;
    testers[1] = &bettertester;

    for (int i=0; i<MAX_LEVEL; ++i)
    {
        int lvl[2];
        lvl[0] = testers[0]->BreakLevel(1, MAX_LEVEL, 2, eggs[i]);
        lvl[1] = testers[1]->BreakLevel(1, MAX_LEVEL, 2, eggs[i]);
        cout << "Egg breaking level: " << lvl[1] << endl;
    }

    return 0;
}