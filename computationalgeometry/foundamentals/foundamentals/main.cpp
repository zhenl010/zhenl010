#include <iostream>
#include "vector_2d.h"
#include "vector_3d.h"
#include "geo_utility_2d.h"
#include "geo_utility_3d.h"
#include "externtest.h"

int factorialIterative(int n) {
    int nfac = 1;
    for (int i=2; i<=n; ++i) {
        nfac *= i;
    }
    return nfac;
}

int factorialRecursive(int n) {
    if (n <= 1) { return 1; }

    return n * factorialRecursive(n-1);
}

struct Node
{
    struct Node* next;
    int val;
};

void reverseAfter( struct Node* head, int val );

Node* reverseList(struct Node* head) {
    Node* newhead = NULL;
    Node* tail = head;
    while (head!=NULL) {
        Node* next = head->next;
        head->next = newhead;
        newhead = head;
        head = next;
    }
    return newhead;
}

void reverseAfter( struct Node* head, int val ) {
    if (head==NULL || head->next==NULL) { return; }

    Node* tail = head;
    while (tail->val!=val && tail->next != NULL) {
        tail = tail->next;
    }
    if (tail == NULL) { return; } // val not found!

    tail = reverseList(tail);
}

// You are implementing simple 'waypoint' following for an AI hover drone 
// in a 3D environment. The drone will consider a destination waypoint 
// acceptable if it is both:
//    i. Less than 10 units away.
//    ii. Inside a 60 degree cone centered around the drone's 'forward' vector.
//
// Implement the function testWayPoint() shown below. If the waypoint is not
// acceptable the method should return REJECTED, otherwise it should return the
// side that the waypoint is on.  This is defined with respect to the drone's
// forward vector and the world up vector (you may choose either 'handedness').

// You may assume the following methods and structures are defined:
using namespace comp_geometry;
typedef Vector3D Vector3;

// Add v and w, putting the result in sum : sum = v + w
void add(const Vector3& v, const Vector3& w, Vector3& sum);

// Subtract w from v, putting the result in diff: diff = v - w
void subtract(const Vector3& v, const Vector3& w, Vector3& diff);

// Compute dot product of Vector3 v and w
float dot(const Vector3& v, const Vector3& w);

// Compute v X w (cross product): crossOut = v X w
void cross(const Vector3& v, const Vector3& w, Vector3& crossOut);

// Normalize the Vector3 v to unit length
void normalize(Vector3& v);

// Compute length of Vector3
float length(const Vector3& v);

enum Direction 
{
    REJECTED = 0,
    RIGHT,
    LEFT
};

// This is the method you must implement:
Direction testWayPoint(const Vector3& dronePosition, const Vector3& droneForward, 
    const Vector3& targetWaypoint, const Vector3& worldUp );

const float DRONE_LENGTH = 10.0f;
const float DRONE_ANGLE_DIFF = 1.0f; // 

// assume droneForward normalized
// Direction testWayPoint(const Vector3& dronePosition, const Vector3& droneForward, 
//     const Vector3& targetWaypoint, const Vector3& worldUp ) {
//     Vector3 dirvec;
//     subtract(targetWaypoint, dronePosition, dirvec);
//     if (length(dirvec) < 10.0f) { return REJECTED; }
//     normalize(dirvec);
//     Vector3 dirdiff;
//     subtract(dirvec, droneForward, dirdiff);
//     if (length(dirdiff) > DRONE_ANGLE_DIFF) { return REJECTED; }
// 
//     Vector3 sidedir;
//     cross(worldUp, droneForward, sidedir);
// 
//     if (dot(sidedir, dirvec) < 0) {
//         return LEFT;
//     } else {
//         return RIGHT; // including drone facing direction ...
//     }
// }

class privateTest {
public:
    int testvalue;

    static int count;
    static privateTest* creatIns(int value){
        ++count;
        return new privateTest(value);
    }
    //static void inherit(){
    // cout<<"inherit"<<endl;
    //}
private:
    privateTest (int value){
        this->testvalue = value;
    }
};

int privateTest::count = 0;

int main(int argc, char** argv) {

    privateTest* pt1 = privateTest::creatIns(1);

    using namespace comp_geometry;

    func();

    int factorial = factorialIterative(3);
    factorial = factorialRecursive(3);

    //////////////////////////////////////////////////////////////////////////
    // 2D tests
    //////////////////////////////////////////////////////////////////////////
    Vector2D pointA(0.0, 0.0);
    Vector2D pointB(1.0, 0.0);
    Vector2D pointP(1.0, 1.0);
    double distance_01a = distanceToLine(pointP, pointA, pointB);
    Line2D lineAB2d(pointB, pointA);
    lineAB2d.normalize();
    double distance_01b = lineAB2d.evaluate(pointP.x, pointP.y);
    Vector2D mirror_point = mirrorPoint(pointP, lineAB2d);

    //////////////////////////////////////////////////////////////////////////
    // 3D tests
    //////////////////////////////////////////////////////////////////////////
    Plane3D plane(1,2,2,-6);
    Vector3D point_3d_01(-1,-2,-3);
    plane.normalize();
    double distance_02a = plane.evaluate(point_3d_01);

    return 0;
}