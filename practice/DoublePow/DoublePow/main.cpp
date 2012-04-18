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

// Special version for performance
double PowDoubleInt(double x, int n)
{
    if (n<0)
    {
        return 1.0 / PowDoubleInt(x, -n);
    }

    double accu = 1.0;
    while (n)
    {
        if ((n&1) != 0)
        {
            accu *= x;
        }
        n>>=1; // math.h exited from here to save a multiply operation
        x *= x;
    }
    return accu;
}

int main(int argc, char** argv)
{
    using namespace std;

    double x = 3.2;
    int n = -6;

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