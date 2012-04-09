#ifndef TEST_EGG_CLASS_H_
#define TEST_EGG_CLASS_H_

namespace aug_puzzle_lib
{
//////////////////////////////////////////////////////////////////////////

class TestEgg
{
public:
    TestEgg() : threshold_(0) {}
    TestEgg(int threshold) : threshold_(threshold) {}

    void Reset(int threshold) { threshold_ = threshold; }

    bool EggBreak(int floor) const { return floor > threshold_; }

private:
    int threshold_;
};

//////////////////////////////////////////////////////////////////////////
}

#endif