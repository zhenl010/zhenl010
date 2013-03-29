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



int main() {
    return 0;
}