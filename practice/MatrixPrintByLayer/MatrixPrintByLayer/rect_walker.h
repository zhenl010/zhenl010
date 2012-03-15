#ifndef RECT_WALKER_H_
#define RECT_WALKER_H_

#include "matrix_rect.h"

// spirally walk through a rect (Clock-wisely)
// one time use only (rect shrink to zero after walking finished)
class RectWalker
{
public:
    static const int DIR_NUM = 4;

    RectWalker(const MatrixRect& rect);

    bool IsValid() { return IsValidRect(rect_); }
    MatrixPosition pos() { return pos_; }
    bool Move();
    int steps() { return max_steps_; }
    void Turn();

private:
    MatrixRect rect_;
    MatrixPosition pos_;
    int cur_dir_;
    int max_steps_;

    void UpdateSteps();
    void UpdateRect();

    struct WalkerHelper
    {
        MatrixPosition inc;
        int constraint_type;
        int constraint_change;
        int step_min;
        int step_max;
    };

    WalkerHelper walker_helpers[DIR_NUM];
};

#endif