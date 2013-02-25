#include "geo_utility_2d.h"
#include <cmath>

namespace comp_geometry {
//------------------------------------------------------------------------

double distanceToLine(const Vector2D& pointP, const Vector2D& vecA, const Vector2D& vecB) {
    return abs(crossProductValue(pointP-vecA, vecB-vecA)) / Distance(vecA, vecB);
    return 0.0;
}

Vector2D reflectionDirection(const Vector2D& incomingVec, const Vector2D& normalVec) {
    Vector2D vout = incomingVec - 2.0*(DotProduct(incomingVec, normalVec))*normalVec;
    return vout.Normalize();
}

double areaTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC) {
    return 0.5 * crossProductValue(vecA-vecB, vecC-vecB);
}

// precondition: plane already normalized
Vector2D mirrorPoint(const Vector2D& point, const Line2D& plane) {
    double signedDist = plane.evaluate(point.x, point.y);
    return Vector2D(point.x-2.0*plane.A_*signedDist, point.y-2.0*plane.B_*signedDist);
}

//------------------------------------------------------------------------
}