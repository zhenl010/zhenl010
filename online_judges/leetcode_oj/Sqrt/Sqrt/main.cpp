#include <iostream>

int Sqrt(int x) {
    int bit = 1<<30;
    int res = 0;

    while (x<bit) { bit >>= 2; }

    while (0 < bit) {
        if (bit+res <= x) {
            x -= (bit+res);
            res = (res>>1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }

    return res; // the last res = 2*r*1 >> 1 = r !!!
}

short isqrt(short num) {
    short res = 0;
    short bit = 1 << 14; // The second-to-top bit is set: 1L<<30 for long

    // "bit" starts at the highest power of four <= the argument.
    while (bit > num)
        bit >>= 2;

    while (bit != 0) {
        if (num >= res + bit) {
            num -= res + bit;
            res = (res >> 1) + bit;
        }
        else
            res >>= 1;
        bit >>= 2;
    }
    return res;
}

int main() {
    for (int i=-1; i<rand();) {
        int x = rand();
        int y = x * x;
        if (Sqrt(y) != x) {
            bool iserror = true;
        }
    }
    int x = isqrt(81);

    return 0;
}