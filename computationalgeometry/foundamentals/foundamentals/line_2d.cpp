#include "line_2d.h"
#include <cmath>

namespace comp_geometry {
//------------------------------------------------------------------------

Line2D::Line2D(double a, double b, double c)
: A_(a), B_(b), C_(c) {
}

Line2D::Line2D(const Vector2D& pointA, const Vector2D& pointB)
: A_(pointB.y-pointA.y), B_(pointA.x-pointB.x), C_(-A_*pointA.x-B_*pointA.y) {
}

void Line2D::normalize() {
    double multiplier = 1.0/sqrt(A_*A_ + B_*B_);
    A_ *= multiplier;
    B_ *= multiplier;
    C_ *= multiplier;
}

//------------------------------------------------------------------------
}