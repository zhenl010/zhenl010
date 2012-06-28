#include <iostream>
#include <cmath>

struct Matrix {
    float mat_[4][4];
};

struct Vector {
    float x; float y; float z;
};

void SetLookAtMatrix(const Vector& Source, const Vector& Target, Matrix &OutLookAtMatrix)
{
    Vector up = {0, 0, 1};
    Vector back = Normalize(Source - Target);
    Vector right = Normalize(CrossProduct(up, back));
    up = Normalize(CrossProduct(back, right));
    // worldToViewMatrix.SetasGlAxes(right, up, back, Source);
    worldToViewMatrix[1][1] = right.x;
    worldToViewMatrix[1][2] = up.x; 
    worldToViewMatrix[1][3] = back.x; 
    worldToViewMatrix[1][4] = 0.0f; 

    worldToViewMatrix[2][1] = right.y; 
    worldToViewMatrix[2][2] = up.y; 
    worldToViewMatrix[2][3] = back.y; 
    worldToViewMatrix[2][4] = 0.0f; 

    worldToViewMatrix[3][1] = right.z; 
    worldToViewMatrix[3][2] = up.z; 
    worldToViewMatrix[3][3] = back.z; 
    worldToViewMatrix[3][4] = 0.0f; 

    worldToViewMatrix[4][1] = -DotProduct(right, source); 
    worldToViewMatrix[4][2] = -DotProduct(up, source);
    worldToViewMatrix[4][3] = -DotProduct(back, source);
    worldToViewMatrix[4][4] = 1.0f;
}

const int CARD_NUM = 52;
void ShuffleDeck(int cards[CARD_NUM])
{
    int temp, index;
    for (int i=0; i<CARD_NUM; ++i)
    {
        index = rand() % (CARD_NUM-i);
        // swap(cards[i], index);
        temp = cards[i];
        cards[i] = cards[index];
        cards[index] = temp;
    }
}

Vector GetProjectileVelocity(const Vector& startPosition, const Vector& targetPosition, float projectileSpeed)
{
    const float gravity = -9.8f;
    float delta = targetPosition.z - startPosition.z; // assuming z-up
    float dxysquare = (targetPosition.x-startPosition.x)*(targetPosition.x-startPosition.x)+
        (targetPosition.y-startPosition.y)*(targetPosition.y-startPosition.y);
    float vsquare = projectileSpeed*projectileSpeed;
    // intermediate variables
    float tmpval_one = sqrt(vsquare*vsquare-gravity *(dxysquare*gravity+2.0f*vsquare*delta));
    float tmpval_two = 2.0f*vsquare*delta*delta + dxysquare*(vsquare+gravity*delta+tmpval_one);
    // firing angle from {0,0,1} up direction
    float cosalpha = sqrt(tmpval_two / (2.0f*vsquare*(dxysquare+delta*delta)));
    float sinalpha = sqrt(1.0 - cosalpha*cosalpha);
    Vector lookat = targetPosition - startPosition;
    lookat.z = 0;
    Normalize(lookat); // Assumed here return {0,0,0} if vector magnitude is zero
    
    return Vector(projectileSpeed*lookat.x*sinalpha, projectileSpeed*lookat.y*sinalpha, projectileSpeed*cosalpha);
}

int main(int argc, char** argv)
{
    using namespace std;
    int cards[CARD_NUM] = { 1, 2, 3, 4, 5 };

    while (1)
    {
        for (int i=0; i<CARD_NUM; ++i)
        {
            cout << cards[i] << ",";
        }
        cout << endl;
        ShuffleDeck(cards);
    }

    return 0;
}