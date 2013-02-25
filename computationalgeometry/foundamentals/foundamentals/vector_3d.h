#ifndef VECTOR_3D_H__
#define VECTOR_3D_H__

#include <cassert>

namespace comp_geometry {
//------------------------------------------------------------------------

// A specific class for 3D world
class Vector3D {
public:
    Vector3D();
    Vector3D(double xIn, double yIn, double zIn);

    double LengthSquare();
    double Length();
    Vector3D& Normalize();

    // operator overload
    Vector3D operator-() const;
    Vector3D& operator*=(double val);
    Vector3D& operator/=(double val);
    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator-=(const Vector3D& rhs);

public: // open access
    double x;
    double y;
    double z;
};

// Explicit component-wise double-Vector3D arithmetic
Vector3D operator+(const Vector3D& vec, double fvalue);
Vector3D operator+(double fvalue, const Vector3D& vec);
Vector3D operator-(const Vector3D& vec, double fvalue);
Vector3D operator-(double fvalue, const Vector3D& vec);
Vector3D operator*(const Vector3D& vec, double scale);
Vector3D operator*(double scale, const Vector3D& vec);
Vector3D operator/(const Vector3D& vec, double scale);

// Explicit Vector3D-Vector3D arithmetic
Vector3D operator+(const Vector3D& vecA, const Vector3D& vecB);
Vector3D operator-(const Vector3D& vecA, const Vector3D& vecB);

Vector3D crossProduct(const Vector3D& vecA, const Vector3D& vecB);
double DotProduct(const Vector3D& vecA, const Vector3D& vecB);
double DistanceSquare(const Vector3D& vecA, const Vector3D& vecB);
double Distance(const Vector3D& vecA, const Vector3D& vecB);

//////////////////////////////////////////////////////////////////////////
// inline function definitions:

inline Vector3D Vector3D::operator-() const {
    return Vector3D(x, y, z);
}

inline Vector3D& Vector3D::operator*=(double val) {
    x *= val;
    y *= val;
    z *= val;
    return *this;
}

inline Vector3D& Vector3D::operator/=(double val) {
    assert(val != 0.0); // caller's responsibility
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

inline Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

// Explicit component-wise double-Vector3D arithmetic

inline Vector3D operator+(const Vector3D& vec, double fvalue) {
    return (Vector3D(vec) += Vector3D(fvalue, fvalue, fvalue));
}

inline Vector3D operator+(double fvalue, const Vector3D& vec) {
    return vec + fvalue;
}

inline Vector3D operator-(const Vector3D& vec, double fvalue) {
    return (Vector3D(vec) -= Vector3D(fvalue, fvalue, fvalue));
}

inline Vector3D operator-(double fvalue, const Vector3D& vec) {
    return ( Vector3D(fvalue, fvalue, fvalue) -= Vector3D(vec) );
}

inline Vector3D operator*(const Vector3D& vec, double scale) {
    return Vector3D(vec.x * scale, vec.y * scale, vec.z * scale);
}

inline Vector3D operator*(double scale, const Vector3D& vec) {
    return vec * scale;
}

inline Vector3D operator/(const Vector3D& vec, double scale) {
    return (Vector3D(vec) /= scale);
}

// Explicit Vector3D-Vector3D arithmetic

inline Vector3D operator+(const Vector3D& vecA, const Vector3D& vecB) {
    return (Vector3D(vecA) += vecB);
}

inline Vector3D operator-(const Vector3D& vecA, const Vector3D& vecB) {
    return (Vector3D(vecA) -= vecB);
}

//------------------------------------------------------------------------
}

#endif