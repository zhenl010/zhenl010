#ifndef PLANE_3D_H__
#define PLANE_3D_H__

#include "vector_3d.h"

namespace comp_geometry {
//------------------------------------------------------------------------

// A specific class for 3D world
class Plane3D {
public:
    Plane3D(double, double, double, double);
    Plane3D(const Vector3D&, const Vector3D&);

    void normalize();
    double evaluate(double x, double y, double z) const { return A_*x+B_*y+C_*z+D_; }
    double evaluate(const Vector3D& v) const { return evaluate(v.x, v.y, v.z); }

public: // open access
    double A_;
    double B_;
    double C_;
    double D_;
};

//------------------------------------------------------------------------
}

#endif