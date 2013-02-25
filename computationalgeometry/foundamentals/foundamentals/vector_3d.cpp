#include "vector_3d.h"
#include <cmath>

namespace comp_geometry
{
//------------------------------------------------------------------------

Vector3D::Vector3D()
    :x(0.0), y(0.0),z(0.0) { // explicitly set to zero
}

Vector3D::Vector3D(double xIn, double yIn, double zIn)
    :x(xIn), y(yIn),z(zIn) {
}

double Vector3D::LengthSquare() {
    return x*x + y*y + z*z;
}

double Vector3D::Length() {
    return sqrt(LengthSquare());
}

Vector3D& Vector3D::Normalize() {
    double invLength = 1 / Length();
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

Vector3D crossProduct(const Vector3D& vecA, const Vector3D& vecB) {
    return Vector3D(
        vecA.y*vecB.z - vecB.z*vecB.y,
        vecA.z*vecB.x - vecB.x*vecB.z,
        vecA.x*vecB.y - vecB.y*vecB.x
        );
}

double DotProduct(const Vector3D& vecA, const Vector3D& vecB) {
    return vecA.x*vecB.x + vecA.y*vecB.y +vecA.z*vecB.z;
}

double DistanceSquare(const Vector3D& vecA, const Vector3D& vecB) {
    return DotProduct(vecA-vecB, vecA-vecB);
}

double Distance(const Vector3D& vecA, const Vector3D& vecB) {
    return sqrt( DistanceSquare(vecA, vecB) );
}

//------------------------------------------------------------------------
}