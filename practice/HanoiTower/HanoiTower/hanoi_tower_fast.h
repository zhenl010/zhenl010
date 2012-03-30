//////////////////////////////////////////////////////////////////////////
// classic Hanoi tower (3 pegs) that write intermediate steps to file
// NOTICE this program is FAST but limit the level to be <64 (i64)
// using array to simulate stack, recursive and iterative Hanoi Tower algorithm
// UPDATE: it turns out this version is not fast lolz...
//////////////////////////////////////////////////////////////////////////
#ifndef HANOI_TOWER_FAST_H_
#define HANOI_TOWER_FAST_H_

namespace puzzle_library
{
//////////////////////////////////////////////////////////////////////////

class HanoiTowerFast
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

    HanoiTowerFast(unsigned char level);
    HANOI_TOWER_ENUM CurrentTower() { return current_; }
    void MoveTo(HANOI_TOWER_ENUM desti);

private:
    // disable copy and assignment
    HanoiTowerFast(const HanoiTowerFast&);
    HanoiTowerFast& operator=(const HanoiTowerFast&);

    // helper functions
    inline unsigned char TopDisk(HANOI_TOWER_ENUM tower);
    inline HANOI_TOWER_ENUM MiddleTower(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void OneLegalMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti);
    void IterativeMove(HANOI_TOWER_ENUM origin, HANOI_TOWER_ENUM desti, HANOI_TOWER_ENUM middle);

    // private data:
    unsigned char level_;
    HANOI_TOWER_ENUM current_;
    unsigned char towers_[TOWER_NUM][MAX_LEVEL+1]; // fixed size for performance
    unsigned char toplvls_[TOWER_NUM];
};

//////////////////////////////////////////////////////////////////////////
}

#endif