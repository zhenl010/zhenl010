#include "hanoi_tower_slow.h"
#include <cassert>
#include <iostream>
#include <stack>

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

// #define COUT_TO_STANDARD_OUTPUT

HanoiTowerSlow::HanoiTowerSlow(int level)
: level_(level), current_(PEG_ONE)
{
    for (int i=0; i<level; ++i)
    {
        towers_[current_].push(level-i);
    }
}

void HanoiTowerSlow::RecursiveMoveTo(HANOI_TOWER_ENUM desti)
{
    RecursiveMoveTo(level_, current_, desti, MiddleTower(current_, desti));
    current_ = desti;
}

void HanoiTowerSlow::IterativeMoveTo(HANOI_TOWER_ENUM desti)
{
    if (level_ <= 0)
    {
        return; // nothing to do
    }

    IterativeMove(current_, desti, MiddleTower(current_, desti));
    current_ = desti;
}

inline HanoiTowerSlow::HANOI_TOWER_ENUM HanoiTowerSlow::MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
    return static_cast<HANOI_TOWER_ENUM>(TOWER_NUM-(current_+desti));
}

void HanoiTowerSlow::OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti)
{
    using namespace std;

    short disk = towers_[origin].top();

#ifdef COUT_TO_STANDARD_OUTPUT
    cout << "disk: " << disk << " from " << origin << " to " << desti << endl;
#endif

    towers_[origin].pop();
    assert(towers_[desti].empty() || disk < towers_[desti].top());
    towers_[desti].push(disk);
}

void HanoiTowerSlow::RecursiveMoveTo(int level, HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle)
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
void HanoiTowerSlow::IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle)
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
    while ( towers_[desti].size()!=level_ )
    {
        // make the next smallest disk's only legal move
        HANOI_TOWER_ENUM peg_left = top_destis[curr_tower];
        HANOI_TOWER_ENUM peg_right = top_destis[peg_left];
        FindNextLegalMove(next_from, next_to, peg_left, peg_right);
        OneLegalMove(next_from, next_to);

        // move the smallest disk:
        OneLegalMove(curr_tower, top_destis[curr_tower]);
        curr_tower = top_destis[curr_tower];
    }
}

void HanoiTowerSlow::FindNextLegalMove(HANOI_TOWER_ENUM& next_from, HANOI_TOWER_ENUM& next_to,
    const HANOI_TOWER_ENUM peg_left, const HANOI_TOWER_ENUM peg_right) const
{
    if (towers_[peg_left].empty())
    {
        next_from = peg_right;
        next_to = peg_left;
    } 
    else if (towers_[peg_right].empty())
    {
        next_from = peg_left;
        next_to = peg_right;
    } else if (towers_[peg_left].top() < towers_[peg_right].top())
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