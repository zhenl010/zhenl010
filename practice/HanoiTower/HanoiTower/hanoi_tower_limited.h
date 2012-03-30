//////////////////////////////////////////////////////////////////////////
// classic Hanoi tower (3 pegs) that write intermediate steps to file
// NOTICE this program is FASTER than the HanoiTowerLimited version
// using array to simulate stack, recursive and iterative Hanoi Tower algorithm
//////////////////////////////////////////////////////////////////////////
#ifndef HANOI_TOWER_LIMITED_H_
#define HANOI_TOWER_LIMITED_H_

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

class HanoiTowerLimited
{
public:
    enum HANOI_TOWER_ENUM
    {
        PEG_ONE = 0,        NO_DISK = 0,        FLOOR_LEVEL = 0,
        PEG_TWO = 1,        
        PEG_THREE = 2,
        TOWER_NUM = 3,
        MAX_LEVEL = 255 // leads to 2^255-1 steps !!!
    };

    HanoiTowerLimited(int level);
    HANOI_TOWER_ENUM CurrentTower() { return current_; }
    void RecursiveMoveTo(HANOI_TOWER_ENUM desti);
    void IterativeMoveTo(HANOI_TOWER_ENUM desti);

private:
    // disable copy and assignment
    HanoiTowerLimited(const HanoiTowerLimited&);
    HanoiTowerLimited& operator=(const HanoiTowerLimited&);

    // helper functions
    inline short TopDisk(HANOI_TOWER_ENUM tower);
    inline HANOI_TOWER_ENUM MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void RecursiveMoveTo(int level, HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle);
    void IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle);
    void FindNextLegalMove(HANOI_TOWER_ENUM& next_from, HANOI_TOWER_ENUM& next_to, HANOI_TOWER_ENUM peg_left, HANOI_TOWER_ENUM peg_right);

    // private data:
    int level_;
    HANOI_TOWER_ENUM current_;
    short towers_[TOWER_NUM][MAX_LEVEL+1]; // fixed size for performance
    short toplvls_[TOWER_NUM];
};

//////////////////////////////////////////////////////////////////////////
}

#endif