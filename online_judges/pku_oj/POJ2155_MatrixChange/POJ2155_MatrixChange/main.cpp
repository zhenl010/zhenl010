#include <cstdio>
#include <cstring>

#pragma warning(disable: 4996)

const int ROW_NUM = 1002;
const int COL_NUM = 1002;
int cnts[ROW_NUM][COL_NUM] = {{}};
int row_num = ROW_NUM;
int col_num = COL_NUM;

int lowbit(int idx) { return idx & (-idx); }

void Update(int x, int y, int delta) {
    int z = y;
    while (x < row_num) {
        z = y;
        while (z < col_num) {
            cnts[x][z] += delta;
            z += lowbit(z);
        }
        x += lowbit(x);
    }
}

// default changes on individual elements '1' and '-1' only
void RangedChange(int x1, int y1, int x2, int y2) {
    Update(x1, y1, 1);
    Update(x2+1, y1, -1);
    Update(x1, y2+1, -1);
    Update(x2+1, y2+1, 1);
}

int Query(int x, int y) {
    int sum = 0;
    int z = y;
    while (x > 0) {
        z = y;
        while (z > 0) {
            sum += cnts[x][z];
            z -= lowbit(z);
        }
        x -= lowbit(x);
    }
    return sum;
}

int main() {
    int X, N, T, x, y, x1, y1, x2, y2;
    char cmd;
    while (scanf("%d", &X) != EOF) {
        for (int i=0; i<X; ++i) {
            scanf("%d %d\n", &N, &T);
            row_num = N+1;
            col_num = N+1;
            memset(cnts, 0, sizeof(cnts));
            for (int j=0; j<T; ++j) {
                scanf("%c", &cmd);
                if (cmd == 'Q') {
                    scanf("%d %d\n", &x, &y);
                    printf("%d\n", Query(x, y) % 2);
                } else if (cmd == 'C') {
                    scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
                    RangedChange(x1, y1, x2, y2);
                }
            }
            printf("\n");
        }
    }
    return 0;
}