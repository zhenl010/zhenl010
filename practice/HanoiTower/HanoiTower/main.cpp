#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include "hanoi_tower.h"

int main(int argc, char** argv)
{
    using namespace std;
    using namespace puzzle_library;

    int tower_level = 24;

    if (argc >= 2)
    {
        string strin = argv[1];
        stringstream str_stream(strin);
        str_stream >> tower_level;
        std::cout << "Tower Level Reset As: " << tower_level << std::endl;
    }

    HanoiTower htower(tower_level);

    time_t startTime;
    time_t endTime;
    time_t timeDiff;

    // timed run
    startTime = time(NULL);
    htower.RecursiveMoveTo(HanoiTower::PEG_THREE);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Recursive move done used time:   " << timeDiff << std::endl << std::endl;

    std::cout << " ++++++++++++++++++++++ " << std::endl;

    startTime = time(NULL);
    htower.IterativeMoveTo(HanoiTower::PEG_TWO);
    endTime = time(NULL);
    timeDiff = (endTime - startTime);
    std::cout << "Iterative move done used time:   " << timeDiff << std::endl << std::endl;

    return 0;
}