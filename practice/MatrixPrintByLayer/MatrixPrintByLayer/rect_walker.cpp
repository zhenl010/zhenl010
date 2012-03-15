#include "rect_walker.h"
#include "matrix_rect.h"

RectWalker::RectWalker(const MatrixRect& rect)
    :rect_(rect), cur_dir_(0) // assume rect is POD
{
    // Init walker by default data @@
    MatrixPosition walkers[] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int constraint_indices[] = { 1, 0, 3, 2 };
    int constraint_changess[] = { 1, 1, -1, -1 };
    int step_mins[] = { 1, 0, 1, 0 };
    int step_maxs[] = { 3, 2, 3, 2 };
    int dir_num = 4;

    for (int i=0; i<DIR_NUM; ++i)
    {
        WalkerHelper helper = { walkers[i], constraint_indices[i], constraint_changess[i], step_mins[i], step_maxs[i] };
        walker_helpers[i] = helper;
    }

    // Start from (0, 0)???
    pos_.i = 0;
    pos_.j = 0;
    UpdateSteps();
}

bool RectWalker::Move()
{
    pos_ = pos_ + walker_helpers[cur_dir_].inc;
    --max_steps_;

    return 0 < max_steps_;
}

void RectWalker::Turn()
{
    cur_dir_ = (cur_dir_+1) % DIR_NUM;
    UpdateSteps();
    UpdateRect();
}

void RectWalker::UpdateSteps()
{
    max_steps_ = rect_.constraints[walker_helpers[cur_dir_].step_max]
               - rect_.constraints[walker_helpers[cur_dir_].step_min];
}

void RectWalker::UpdateRect()
{
    rect_.constraints[walker_helpers[cur_dir_].constraint_type] += walker_helpers[cur_dir_].constraint_change;
}