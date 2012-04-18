#ifndef GAME_TWENTY_FOUR_H_
#define GAME_TWENTY_FOUR_H_

#include <string>
#include "int_fraction.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class GameTwentyFour
{
public:
    static const int ACTIVE_CARD_NUM = 4;
    static const int VALID_OPERATOR_NUM = 4;

    GameTwentyFour(int, int, int, int);
    bool IsSolvable() { return !ans_.empty(); }
    void Update(); // update answer if found
    std::string Answer() { return ans_; }

private:
    // static IntFraction target_ = IntFraction(24, 1);
    int nums_[ACTIVE_CARD_NUM];
    std::string ans_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif