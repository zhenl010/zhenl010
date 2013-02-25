// template<class _Ty> inline
//     _Ty _Pow_int(_Ty _X, int _Y)
// {unsigned int _N;
// if (_Y >= 0)
//     _N = (unsigned int)_Y;
// else
//     _N = (unsigned int)(-_Y);
// for (_Ty _Z = _Ty(1); ; _X *= _X)
// {if ((_N & 1) != 0)
// _Z *= _X;
// if ((_N >>= 1) == 0)
//     return (_Y < 0 ? _Ty(1) / _Z : _Z); }}
#include <iostream>
#include <cmath>

#define SPEC_CHAR_ARRY {0, 1, 2, 3, 4, 5, 6, 255}

void init_f (void)
{
    char c[] = SPEC_CHAR_ARRY;

    // do sth ...
}

// Special version for performance
double PowDoubleInt(double x, int n)
{
    if(n<0) return 1.0/(x*PowDoubleInt(x, -(n+1)));

    double y = 1.0;
    while(n > 0) {
        if((n&1) > 0) {
            y *= x;
        }
        n >>= 1;
        if(!n) return y;
        x *= x;
    }
    return y;
}

int main(int argc, char** argv)
{
    using namespace std;

    double x = -2.0;
    int n = -2147483648;

    double y = pow(x, n);
    double ytest = PowDoubleInt(x, n);

    if (y != ytest)
    {
        cout << y - ytest << endl;
    }

    double t = 2.3;
    double result = pow(x, t);

    return 0;
}