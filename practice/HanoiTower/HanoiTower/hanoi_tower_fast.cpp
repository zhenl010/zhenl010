// #define COUT_TO_STANDARD_OUTPUT
#include "hanoi_tower_fast.h"
#include <cassert>
#include <limits>
#ifdef COUT_TO_STANDARD_OUTPUT
#include <iostream>
#endif

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

HanoiTowerFast::HanoiTowerFast(unsigned char level)
: level_(level), current_(PEG_ONE)
{
    assert(level<=MAX_LEVEL);
    for (unsigned char tow=PEG_ONE; tow<TOWER_NUM; ++tow)
    {
        for (int i=0; i<level; ++i)
        {
            towers_[tow][i] = UCHAR_MAX;
        }
    }

    for (int i=1; i<level+1; ++i)
    {
        towers_[PEG_ONE][i] = (level+1-i);
        towers_[PEG_TWO][i] = NO_DISK;
        towers_[PEG_THREE][i] = NO_DISK;
    }

    toplvls_[PEG_ONE] = level;
    toplvls_[PEG_TWO] = FLOOR_LEVEL;
    toplvls_[PEG_THREE] = FLOOR_LEVEL;
}

void HanoiTowerFast::MoveTo(HANOI_TOWER_ENUM desti)
{
    if (level_ <= 0)
    {
        return; // nothing to do
    }

    IterativeMove(current_, desti, MiddleTower(current_, desti));
    current_ = desti;
}

inline unsigned char HanoiTowerFast::TopDisk(HANOI_TOWER_ENUM tower)
{
    return towers_[tower][toplvls_[tower]];
}

inline HanoiTowerFast::HANOI_TOWER_ENUM HanoiTowerFast::MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
    return static_cast<HANOI_TOWER_ENUM>(TOWER_NUM-(current_+desti));
}

void HanoiTowerFast::OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
#ifdef COUT_TO_STANDARD_OUTPUT
    using namespace std;
    unsigned char disk = TopDisk(origin);
    cout << "disk: " << disk << " from " << origin << " to " << desti << endl;
#endif

    ++toplvls_[desti];
    towers_[desti][toplvls_[desti]] = towers_[origin][toplvls_[origin]];
    towers_[origin][toplvls_[origin]] = NO_DISK;
    --toplvls_[origin];
}

void HanoiTowerFast::IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle)
{
    long long int x;
    unsigned long long int i;
    int fr, to;
    HANOI_TOWER_ENUM tower_map[] = { origin, middle, desti };
    for (x=1; x < (1i64 << level_); x++)
    {
        i=x&x-1;
        fr=(i+i/3)&3;
        i=(x|x-1)+1; to=(i+i/3)&3;
        OneLegalMove(tower_map[fr], tower_map[to]);
    }
}

//////////////////////////////////////////////////////////////////////////
}