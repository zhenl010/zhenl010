//////////////////////////////////////////////////////////////////////////
// classic Hanoi tower (3 pegs) that write intermediate steps to file
// NOTICE THIS PROGRAM IS VERY VERY SLOW DUE TO THE USE OF stack
// just a practice on stack, recursive and iterative Hanoi Tower algorithm
//////////////////////////////////////////////////////////////////////////
#ifndef HANOI_TOWER_SLOW_H_
#define HANOI_TOWER_SLOW_H_

#include <stack>

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

class HanoiTowerSlow
{
public:
    enum HANOI_TOWER_ENUM
    {
        PEG_ONE = 0,
        PEG_TWO = 1,
        PEG_THREE = 2,
        TOWER_NUM = 3
    };

    HanoiTowerSlow(int level);
    HANOI_TOWER_ENUM CurrentTower() { return current_; }
    void RecursiveMoveTo(HANOI_TOWER_ENUM desti);
    void IterativeMoveTo(HANOI_TOWER_ENUM desti);

private:
    // disable copy and assignment
    HanoiTowerSlow(const HanoiTowerSlow&);
    HanoiTowerSlow& operator=(const HanoiTowerSlow&);

    // helper functions
    inline HANOI_TOWER_ENUM MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void RecursiveMoveTo(int level, HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle);
    void IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle);
    void FindNextLegalMove(HANOI_TOWER_ENUM& next_from, HANOI_TOWER_ENUM& next_to, HANOI_TOWER_ENUM peg_left, HANOI_TOWER_ENUM peg_right) const;

    // private data:
    int level_;
    HANOI_TOWER_ENUM current_;
    std::stack<short> towers_[TOWER_NUM];
};

//////////////////////////////////////////////////////////////////////////
}

#endif