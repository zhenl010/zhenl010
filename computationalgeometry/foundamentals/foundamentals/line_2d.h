#ifndef LINE_2d_H__
#define LINE_2d_H__

#include "vector_2d.h"

namespace comp_geometry {
//------------------------------------------------------------------------

// A specific class for 3D world
class Line2D {
public:
    Line2D(double, double, double);
    Line2D(const Vector2D&, const Vector2D&);

    void normalize();
    double evaluate(double x, double y) const { return A_*x+B_*y+C_; }

public: // open access
    double A_;
    double B_;
    double C_;
};

//------------------------------------------------------------------------
}

#endif