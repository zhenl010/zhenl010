#include <iostream>
#include <cassert>
#include "rect_walker.h"

namespace // unnamed namespace
{
//////////////////////////////////////////////////////////////////////////

const int ROW_NUM = 3;
const int COL_NUM = 4;

// intuitive version that print layer by layer, and a stand-alone version
void CoutByLayer(const int mat[ROW_NUM][COL_NUM])
{
    if (ROW_NUM<=0 || COL_NUM<=0)
    {
        return;
    }

    using namespace std;

    for (int layer=0; layer<=(min(ROW_NUM, COL_NUM)-1)/2; ++layer)
    {
        for (int i=layer, j=layer; j<COL_NUM-layer; ++j)
        {
            cout << mat[i][j] << " ";
        }

        if (ROW_NUM-layer-1 != layer) // degenerate case
        {
            for (int i=layer+1, j=COL_NUM-layer-1; i<ROW_NUM-layer-1; ++i)
            {
                cout << mat[i][j] << " ";
            }

            for (int i=ROW_NUM-layer-1, j=COL_NUM-layer-1; j>=layer; --j)
            {
                cout << mat[i][j] << " ";
            }

            if (COL_NUM-layer-1 != layer) // degenerate case
            {
                for (int i=ROW_NUM-layer-2, j=layer; i>layer; --i)
                {
                    cout << mat[i][j] << " ";
                }
            }
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void CoutMatrix(const int mat[ROW_NUM][COL_NUM])
{
    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// hopefully most efficient version
void PrintMatrixClockwisely(const int mat[ROW_NUM][COL_NUM])
{
    assert(0<ROW_NUM && 0<COL_NUM);

    MatrixRect rect = { 0, 0, ROW_NUM-1, COL_NUM-1 };
    // Init walker
    MatrixPosition walkers[] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int constraint_indices[] = { 1, 0, 3, 2 };
    int constraint_changess[] = { 1, 1, -1, -1 };
    int step_mins[] = { 1, 0, 1, 0 };
    int step_maxs[] = { 3, 2, 3, 2 };
    int dir_num = 4;
    MatrixPosition pos = { 0, 0 }; // starting position designed
    std::cout << mat[pos.i][pos.j] << " ";
    int cur_dir=0;
    int steps[4];
    steps[cur_dir] = rect.constraints[step_maxs[cur_dir]]-rect.constraints[step_mins[cur_dir]];
    while (IsValidRect(rect))
    {
        for (int i=0; i<steps[cur_dir]; ++i)
        {
            pos = pos + walkers[cur_dir];
            std::cout << mat[pos.i][pos.j] << " ";
        }

        cur_dir = (cur_dir+1) % dir_num;
        // Calculate next step before shrink rect is easier to implement @@
        steps[cur_dir] = rect.constraints[step_maxs[cur_dir]]-rect.constraints[step_mins[cur_dir]];
        rect.constraints[constraint_indices[cur_dir]] += constraint_changess[cur_dir];
    }
    std::cout << std::endl;
}

// Use walker to print matrix spirally
void SpiralPrintMatrix(const int mat[ROW_NUM][COL_NUM])
{
    if (ROW_NUM<=0 || COL_NUM<=0)
    {
        return;
    }

    MatrixRect rect = { 0, 0, ROW_NUM-1, COL_NUM-1 };
    RectWalker walker(rect);
    std::cout << mat[walker.pos().i][walker.pos().j] << " ";
    while (walker.IsValid())
    {
        // notice walker.steps() changes after every move
        int steps = walker.steps();
        for (int i=0; i<steps; ++i)
        {
            walker.Move();
            std::cout << mat[walker.pos().i][walker.pos().j] << " ";
        }

        walker.Turn();
    }
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
}

int main()
{
    int mat[ROW_NUM][COL_NUM];
    for (int i=0; i<ROW_NUM; ++i)
    {
        for (int j=0; j<COL_NUM; ++j)
        {
            mat[i][j] = i*COL_NUM + j;
        }
    }

    CoutMatrix(mat);

    CoutByLayer(mat);

    PrintMatrixClockwisely(mat);

    std::cout << std::endl;

    SpiralPrintMatrix(mat);

    return 0;
}