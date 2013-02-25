#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace integer_computational_geometry {
//////////////////////////////////////////////////////////////////////////
using namespace std;

struct Vector2D {
    typedef int ValueType;
    ValueType x;
    ValueType y;
};

Vector2D vector2DFromString(string str) {
    stringstream sstrm(str);
    Vector2D vac;
    sstrm >> vac.x;
    sstrm >> vac.y;
    return vac;
}

enum POINT_LINE_RELATIONSHIP {
    LEFT,
    LIESWITHIN,
    LIESOUT,
    RIGHT
};

POINT_LINE_RELATIONSHIP pointLineRelation(const Vector2D &pointP, const Vector2D &pointA, const Vector2D &pointB) {
    Vector2D::ValueType testval = (pointP.y-pointA.y)*(pointB.x-pointA.x) - (pointP.x-pointA.x)*(pointB.y-pointA.y);
    if (testval < 0) {
        return LEFT;
    } else if (testval > 0) {
        return RIGHT;
    }

    if(((pointP.x<pointA.x) == (pointP.x<pointB.x)) || ((pointP.y<pointA.y) == (pointP.y<pointB.y))) {
        return LIESOUT;
    } else {
        return LIESWITHIN;
    }
}

// precondition: The horizontal line do intersect with the line segment
Vector2D::ValueType intersectPoint(Vector2D::ValueType y, const Vector2D &pointA, const Vector2D &pointB) {
    return pointA.x+(y-pointA.y)/(pointB.y-pointA.y)*(pointB.x-pointA.x);
}

class PointInSimplePolygon {
public:
    // precondition: vertices are always valid! (no input error check)
    // number of vertices at least equals 3
    static string testPoint(const Vector2D point, const vector<Vector2D> vertices);
    static bool isOnBoundary(const Vector2D point, const vector<Vector2D> vertices);
};

bool PointInSimplePolygon::isOnBoundary(const Vector2D point, const vector<Vector2D> vertices) {
    // local loop variables
    size_t i = 0;
    size_t j = vertices.size() - 1;
    // check "BOUNDARY" case first
    while (i<vertices.size()) {
        POINT_LINE_RELATIONSHIP relation = pointLineRelation(point, vertices[i], vertices[j]);
        if (relation == LIESWITHIN) { return true; }
        j = i++;
    }
    return false;
}

string PointInSimplePolygon::testPoint(const Vector2D point, const vector<Vector2D> vertices) {
    if (isOnBoundary(point, vertices)) { return string("BOUNDARY"); }

    // local loop variables
    bool oddNodes = false;
    size_t i = 0;
    size_t j = vertices.size() - 1;
    // check "BOUNDARY" case first
    while (i<vertices.size()) {
        // test only if intersect with horizontal line passing point
        if ( (vertices[i].y<point.y && point.y<=vertices[j].y)
            || (vertices[j].y<point.y && point.y<=vertices[i].y) ) {
            if (intersectPoint(point.y, vertices[i], vertices[j]) < point.x) {
                oddNodes = !oddNodes; // flip if cross one valid edge
            }
        }
        j = i++;
    }

    return oddNodes ? string("INTERIOR") : string("EXTERIOR");
}

//////////////////////////////////////////////////////////////////////////
}

using namespace std;
using namespace integer_computational_geometry;

class PointInPolygon {
public:
    // precondition vertices are always valid! (no input error check)
    // number of vertices at least equals 3
    string testPoint(vector <string> vertices, int testPointX, int testPointY) {
        vector<Vector2D> verts(vertices.size());
        for (size_t i=0; i<verts.size(); ++i) {
            verts[i] = vector2DFromString(vertices[i]);
        }
        Vector2D point = { testPointX, testPointY };
        return PointInSimplePolygon::testPoint(point, verts);
    }
};

int main(int argc, char** argv) {
    Vector2D point = { 5, 5 };
    vector<string> vertStrs;
    vertStrs.push_back("0 0");
    vertStrs.push_back("0 10");
    vertStrs.push_back("10 10");
    vertStrs.push_back("10 0");

    PointInPolygon solver;
    string relationString = solver.testPoint(vertStrs, point.x, point.y);


    return 0;
}