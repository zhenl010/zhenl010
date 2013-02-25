#ifndef VECTOR_2D_H__
#define VECTOR_2D_H__

namespace comp_geometry {
//------------------------------------------------------------------------

// A specific class for 3D world
class Vector2D {
public:
    Vector2D();
    Vector2D(double xIn, double yIn);

    double LengthSquare();
    double Length();
    Vector2D& Normalize();

    // operator overload
    Vector2D operator-() const;
    Vector2D& operator*=(double val);
    Vector2D& operator/=(double val);
    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator-=(const Vector2D& rhs);

public: // open access
    double x;
    double y;
};

// Explicit component-wise double-Vector2D arithmetic
Vector2D operator+(const Vector2D& vec, double fvalue);
Vector2D operator+(double fvalue, const Vector2D& vec);
Vector2D operator-(const Vector2D& vec, double fvalue);
Vector2D operator-(double fvalue, const Vector2D& vec);
Vector2D operator*(const Vector2D& vec, double scale);
Vector2D operator*(double scale, const Vector2D& vec);
Vector2D operator/(const Vector2D& vec, double scale);

// Explicit Vector2D-Vector2D arithmetic
Vector2D operator+(const Vector2D& vecA, const Vector2D& vecB);
Vector2D operator-(const Vector2D& vecA, const Vector2D& vecB);

double DotProduct(const Vector2D& vecA, const Vector2D& vecB);
double crossProductValue(const Vector2D& vecA, const Vector2D& vecB);
double DistanceSquare(const Vector2D& vecA, const Vector2D& vecB);
double Distance(const Vector2D& vecA, const Vector2D& vecB);

//////////////////////////////////////////////////////////////////////////
// inline function definitions:

inline Vector2D Vector2D::operator-() const {
    return Vector2D(x, y);
}

inline Vector2D& Vector2D::operator*=(double val) {
    x *= val;
    y *= val;
    return *this;
}

// assert(val != 0.0); // caller's responsibility
inline Vector2D& Vector2D::operator/=(double val) {
    x /= val;
    y /= val;
    return *this;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

// Explicit component-wise double-Vector2D arithmetic

inline Vector2D operator+(const Vector2D& vec, double fvalue) {
    return (Vector2D(vec) += Vector2D(fvalue, fvalue));
}

inline Vector2D operator+(double fvalue, const Vector2D& vec) {
    return vec + fvalue;
}

inline Vector2D operator-(const Vector2D& vec, double fvalue) {
    return (Vector2D(vec) -= Vector2D(fvalue, fvalue));
}

inline Vector2D operator-(double fvalue, const Vector2D& vec) {
    return ( Vector2D(fvalue, fvalue) -= Vector2D(vec) );
}

inline Vector2D operator*(const Vector2D& vec, double scale) {
    return Vector2D(vec.x * scale, vec.y * scale);
}

inline Vector2D operator*(double scale, const Vector2D& vec) {
    return vec * scale;
}

inline Vector2D operator/(const Vector2D& vec, double scale) {
    return (Vector2D(vec) /= scale);
}

// Explicit Vector2D-Vector2D arithmetic

inline Vector2D operator+(const Vector2D& vecA, const Vector2D& vecB) {
    return (Vector2D(vecA) += vecB);
}

inline Vector2D operator-(const Vector2D& vecA, const Vector2D& vecB) {
    return (Vector2D(vecA) -= vecB);
}

//------------------------------------------------------------------------
}

#endif