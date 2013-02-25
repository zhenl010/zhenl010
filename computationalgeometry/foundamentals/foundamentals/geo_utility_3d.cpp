#include "geo_utility_3d.h"
#include <cmath>

namespace comp_geometry {
//------------------------------------------------------------------------

double distanceToLine(const Vector3D& pointP, const Vector3D& vecA, const Vector3D& vecB) {
    return crossProduct(pointP-vecA, vecB-vecA).Length() / Distance(vecA, vecB);
}

Vector3D reflectionDirection(const Vector3D& incomingVec, const Vector3D& normalVec) {
    Vector3D vout = incomingVec - 2.0*(DotProduct(incomingVec, normalVec))*normalVec;
    return vout.Normalize();
}

double areaTriangle(const Vector3D& vecA, const Vector3D& vecB, const Vector3D& vecC) {
    return 0.5 * crossProduct(vecA-vecB, vecC-vecB).Length();
}

//------------------------------------------------------------------------
}