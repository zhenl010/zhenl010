#include <cstdio>

#pragma warning(disable: 4996)

int lowbit(int x) { return x & (-x); }

bool IsOn(int n, int k) {
    if ((1<<n) <= lowbit(k+1)) return true;
    return false;
}

void PrintInt(int x) {
    for (char i=0; i<32; ++i) {
        if (x & 1) { putchar('1'); } else { putchar('0'); }
        x >>= 1;
    }
}

int main() {
    int t, n, k;
    scanf("%d", &t);
    for(int i=1; i<=t; ++i) {
        printf("Case #%d: ", i);
        scanf("%d %d", &n, &k);
        if (IsOn(n, k)) {
            puts("ON");
        } else {
            puts("OFF");
        }
    }
}