#include "hanoi_tower_limited.h"
#include <cassert>
#include <iostream>

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

// #define COUT_TO_STANDARD_OUTPUT

HanoiTowerLimited::HanoiTowerLimited(int level)
: level_(level), current_(PEG_ONE)
{
    assert(level<=MAX_LEVEL);
    for (short tow=PEG_ONE; tow<TOWER_NUM; ++tow)
    {
        for (int i=0; i<level; ++i)
        {
            towers_[tow][i] = SHRT_MAX;
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

void HanoiTowerLimited::RecursiveMoveTo(HANOI_TOWER_ENUM desti)
{
    RecursiveMoveTo(level_, current_, desti, MiddleTower(current_, desti));
    current_ = desti;
}

void HanoiTowerLimited::IterativeMoveTo(HANOI_TOWER_ENUM desti)
{
    if (level_ <= 0)
    {
        return; // nothing to do
    }

    IterativeMove(current_, desti, MiddleTower(current_, desti));
    current_ = desti;
}

inline short HanoiTowerLimited::TopDisk(HANOI_TOWER_ENUM tower)
{
    return towers_[tower][toplvls_[tower]];
}

inline HanoiTowerLimited::HANOI_TOWER_ENUM HanoiTowerLimited::MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
    return static_cast<HANOI_TOWER_ENUM>(TOWER_NUM-(current_+desti));
}

void HanoiTowerLimited::OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
    using namespace std;

    short disk = TopDisk(origin);

#ifdef COUT_TO_STANDARD_OUTPUT
    cout << "disk: " << disk << " from " << origin << " to " << desti << endl;
#endif

    ++toplvls_[desti];
    towers_[desti][toplvls_[desti]] = towers_[origin][toplvls_[origin]];
    towers_[origin][toplvls_[origin]] = NO_DISK;
    --toplvls_[origin];
}

void HanoiTowerLimited::RecursiveMoveTo(int level, HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle)
{
    if (level==0)
    {
        return;
    }

    RecursiveMoveTo(level-1, origin, middle, desti);
    OneLegalMove(origin, desti);
    RecursiveMoveTo(level-1, middle, desti, origin);
}

/// @TODO:
void HanoiTowerLimited::IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle)
{
    // Smallest disk's position
    HANOI_TOWER_ENUM curr_tower = origin;

    HANOI_TOWER_ENUM top_destis[TOWER_NUM];
    if (level_ % 2 == 0) // CLOCL_WISE
    {
        top_destis[origin] = middle;
        top_destis[middle] = desti;
        top_destis[desti] = origin;
    } 
    else // COUNTER_CLOCL_WISE
    {
        top_destis[origin] = desti;
        top_destis[desti] = middle;
        top_destis[middle] = origin;
    }

    // move the smallest disk:
    OneLegalMove(curr_tower, top_destis[curr_tower]);
    curr_tower = top_destis[curr_tower];
    HANOI_TOWER_ENUM next_from;
    HANOI_TOWER_ENUM next_to;
    // make the next smallest disk's only legal move
    HANOI_TOWER_ENUM peg_left;
    HANOI_TOWER_ENUM peg_right;
    while ( toplvls_[desti] < level_ )
    {
        // make the next smallest disk's only legal move
        peg_left = top_destis[curr_tower];
        peg_right = top_destis[peg_left];
        FindNextLegalMove(next_from, next_to, peg_left, peg_right);
        OneLegalMove(next_from, next_to);

        // move the smallest disk:
        OneLegalMove(curr_tower, top_destis[curr_tower]);
        curr_tower = top_destis[curr_tower];
    }
}

void HanoiTowerLimited::FindNextLegalMove(HANOI_TOWER_ENUM& next_from, HANOI_TOWER_ENUM& next_to,
    const HANOI_TOWER_ENUM peg_left, const HANOI_TOWER_ENUM peg_right)
{
    if ( TopDisk(peg_left) < TopDisk(peg_right) )
    {
        next_from = peg_left;
        next_to = peg_right;
    } 
    else
    {
        next_from = peg_right;
        next_to = peg_left;
    }
}

//////////////////////////////////////////////////////////////////////////
}