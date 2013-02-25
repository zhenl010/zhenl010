#include "vector_2d.h"
#include <cmath>

namespace comp_geometry {
//------------------------------------------------------------------------

Vector2D::Vector2D()
:x(0.0), y(0.0) { // explicitly set to zero
}

Vector2D::Vector2D(double xIn, double yIn)
:x(xIn), y(yIn) {
}

double Vector2D::LengthSquare() {
    return x*x + y*y;
}

double Vector2D::Length() {
    return sqrt(LengthSquare());
}

Vector2D& Vector2D::Normalize() {
    double invLength = 1 / Length();
    x *= invLength;
    y *= invLength;
    return *this;
}

inline double DotProduct(const Vector2D& vecA, const Vector2D& vecB) {
    return vecA.x*vecB.x + vecA.y*vecB.y;
}

double crossProductValue(const Vector2D& vecA, const Vector2D& vecB) {
    return vecA.x*vecB.y - vecA.y*vecB.x;
}

double DistanceSquare(const Vector2D& vecA, const Vector2D& vecB) {
    return DotProduct(vecA-vecB, vecA-vecB);
}

double Distance(const Vector2D& vecA, const Vector2D& vecB) {
    return sqrt( DistanceSquare(vecA, vecB) );
}

//------------------------------------------------------------------------
}