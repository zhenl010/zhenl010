#include <cstdio>

#pragma warning(disable: 4996)

const short kMaxN = 15002;
const short kMaxX = 32002;
short lvls[kMaxX] = {};
short cnts[kMaxN] = {};

inline short lowbit(short idx) { return idx & (-idx); }

void Update(short idx, short delta) {
    while (idx>0 && idx<kMaxX) {
        lvls[idx] += delta;
        idx += lowbit(idx);
    }
}

short GetLvl(short idx) {
    short lvl = 0;
    while (idx>0) {
        lvl += lvls[idx];
        idx -= lowbit(idx);
    }
    return lvl;
}

int main() {
    int n, x, y;
    while (scanf("%d", &n) != EOF) {
        for (short i=0; i<n; ++i) {
            scanf("%d %d", &x, &y);
            ++cnts[GetLvl(x+1)];
            Update(x+1, 1);
        }

        for (short i=0; i<n; ++i) {
            printf("%d\n", cnts[i]);
        }
    }
    return 0;
}