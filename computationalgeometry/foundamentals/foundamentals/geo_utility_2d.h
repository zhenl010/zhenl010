#ifndef GEO_UTILITY_2D_H__
#define GEO_UTILITY_2D_H__

#include "common_consts.h"
#include "vector_2d.h"
#include "line_2d.h"

namespace comp_geometry {
//------------------------------------------------------------------------

// the distance from a point P to line AB, assume A,B never overlap
double distanceToLine(const Vector2D&, const Vector2D&, const Vector2D&);

Vector2D reflectionDirection(const Vector2D&, const Vector2D&);

double areaTriangle(const Vector2D&, const Vector2D&, const Vector2D&);

Vector2D mirrorPoint(const Vector2D&, const Line2D&);

//------------------------------------------------------------------------
}

#endif