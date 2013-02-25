#ifndef GEO_UTILITY_3D_H__
#define GEO_UTILITY_3D_H__

#include "common_consts.h"
#include "vector_3d.h"
#include "plane_3d.h"

namespace comp_geometry {
//------------------------------------------------------------------------

// the distance from a point P to line AB, assume A,B never overlap
double distanceToLine(const Vector3D&, const Vector3D&, const Vector3D&);

Vector3D reflectionDirection(const Vector3D&, const Vector3D&);

double areaTriangle(const Vector3D&, const Vector3D&, const Vector3D&);

//------------------------------------------------------------------------
}

#endif