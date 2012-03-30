#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include "hanoi_tower_slow.h"
#include "hanoi_tower_limited.h"
#include "hanoi_tower_fast.h"

namespace // unnamed
{
    void FastHanoiSolver(short level)
    {
        long long int x;
        unsigned long long int i;
        int fr, to;
        for (x=1; x < (1i64 << level); x++)
        {
            i=x&x-1;
            fr=(i+i/3)&3;
            i=(x|x-1)+1; to=(i+i/3)&3;
            // printf( "move from pole %i to pole %i.\n", to, fr );
        }
    }
}

int main(int argc, char** argv)
{
    using namespace std;
    using namespace puzzle_library;

    int tower_level = 4;

    if (argc >= 2)
    {
        string strin = argv[1];
        stringstream str_stream(strin);
        str_stream >> tower_level;
        std::cout << "Tower Level Reset As: " << tower_level << std::endl;
    }

    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    HanoiTowerFast htower_fast(tower_level);

    // timed run
    startTime = time(NULL);
    htower_fast.MoveTo(HanoiTowerFast::PEG_THREE);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Fast but limited (lvl<64) move done used time: " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl << std::endl;
    
    HanoiTowerLimited htower_limited(tower_level);

    // timed run
    startTime = time(NULL);
    htower_limited.RecursiveMoveTo(HanoiTowerLimited::PEG_THREE);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Recursive move done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl << std::endl;

    startTime = time(NULL);
    htower_limited.IterativeMoveTo(HanoiTowerLimited::PEG_TWO);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Iterative move done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl << std::endl;

    // fast hanoi-tower solver found on-line (binary solution)
    startTime = time(NULL);
    FastHanoiSolver(tower_level);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Fast (raw) Hanoi tower solver done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl << std::endl;

    HanoiTowerSlow htower_slow(tower_level);

    // timed run
    startTime = time(NULL);
    htower_slow.RecursiveMoveTo(HanoiTowerSlow::PEG_THREE);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Recursive move done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl << std::endl;

    startTime = time(NULL);
    htower_slow.IterativeMoveTo(HanoiTowerSlow::PEG_TWO);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Iterative move done used time:   " << timeDiff << std::endl << std::endl;

    return 0;
}