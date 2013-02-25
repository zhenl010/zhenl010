#include "plane_3d.h"
#include <cmath>

namespace comp_geometry {
//------------------------------------------------------------------------

Plane3D::Plane3D(double a, double b, double c, double d)
: A_(a), B_(b), C_(c), D_(d) {
}

Plane3D::Plane3D(const Vector3D& point, const Vector3D& normal)
: A_(normal.x), B_(normal.y), C_(normal.z)
, D_(-(normal.x*point.x+normal.y*point.y+normal.z*point.z)) {
}

void Plane3D::normalize() {
    double multiplier = 1.0/sqrt(A_*A_ + B_*B_+C_*C_);
    A_ *= multiplier;
    B_ *= multiplier;
    C_ *= multiplier;
    D_ *= multiplier;
}

//------------------------------------------------------------------------
}