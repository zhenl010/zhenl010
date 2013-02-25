//////////////////////////////////////////////////////////////////////////
// Problem Statement for TVTower
// Our problem is where to locate our TV station's broadcasting tower. We know the locations
// of the towns we should serve. Fortunately, we are located on the flat, flat prairie, so
// the only issue is where to locate the tower to minimize the broadcast radius that includes
// all the towns. We have int[] x and int[] y giving the locations of the towns; the i-th
// elements of x and y give the coordinates of the i-th town.
// Create a class TVTower that contains a method minRadius that is given x and y,
// and returns the minimum broadcast radius that can reach all the towns.
// The tower's location is NOT restricted to integer coordinates.
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const double EPISILON = 1.0E-9;

struct Vector2D {
    double x;
    double y;
};

double dotProduct(const Vector2D &pointA, const Vector2D &pointB) {
    return pointA.x*pointB.x + pointA.y*pointB.y;
}

double distanceBetween(const Vector2D &pointA, const Vector2D &pointB) {
    Vector2D vecAtoB = { pointB.x-pointA.x, pointB.y-pointA.y };
    return sqrt( dotProduct(vecAtoB, vecAtoB) );
}

// precondition these three points are not on the same line!
double radiusCircleFromThreePoints(double xa, double ya, double xb, double yb, double xc, double yc) {
    double denominator = 2.0*( xc*(yb-ya) + xb*(ya-yc) + xa*(yc-yb) );
    assert( abs(denominator)>EPISILON );
    double xcenter = xc*xc*(yb-ya) + xb*xb*(ya-yc) - (xa*xa + (ya-yb)*(ya-yc))*(yb-yc);
    double ycenter = -xb*xb*xc + xa*xa*(xc-xb) + xc*(ya-yb)*(ya+yb)
        + xa*(xb*xb - xc*xc + yb*yb - yc*yc) + xb*(xc*xc - ya*ya + yc*yc);
    Vector2D centerPoint = { xcenter/denominator, ycenter/denominator };
    Vector2D pointA = {xa, ya};
    Vector2D pointB = {xb, yb};
    Vector2D pointC = {xc, yc};
    assert( distanceBetween(centerPoint, pointA)==distanceBetween(centerPoint, pointB) );
    assert( distanceBetween(centerPoint, pointB)==distanceBetween(centerPoint, pointC) );
    return distanceBetween(centerPoint, pointA);
};

class TVTower {
public:
    double minRadius(vector <int> x, vector <int> y) {
        double radius = 0.0;
        return radius;
    }

private:

};

int main(int argc, char** argv) {
    return 0;
}