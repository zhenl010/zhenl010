#ifndef MATRIX_RECT_H_
#define MATRIX_RECT_H_

// implement same function with walker
struct MatrixPosition
{
    int i;
    int j;
};

inline const MatrixPosition operator+(const MatrixPosition& lval, const MatrixPosition& rval)
{
    MatrixPosition result = { lval.i + rval.i, lval.j + rval.j };
    return result;
}

struct MatrixRect
{
    int constraints[4];
};

inline bool IsValidRect(const MatrixRect& rect)
{
    return !( rect.constraints[2]<rect.constraints[0] || rect.constraints[3]<rect.constraints[1] );
}

#endif