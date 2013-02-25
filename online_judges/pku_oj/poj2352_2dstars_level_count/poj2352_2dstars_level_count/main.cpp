#include<iostream>

// Notice -i = ~i + 1;
#define lowbit(x) (x & (-x))

const int MAX_LVL = 15002;
const int MAX_X = 32002;

// index starts from 1, end at N
inline int Query(const int* t, int i) {
    int sum = 0;
    while (i > 0) {
        sum += t[i];
        i -= lowbit(i);
    }
    return sum;
}

// index starts from 1, end at N
inline void Update(int* t, int N, int i, int x) {
    while (i < N) {
        t[i] += x;
        i += lowbit(i);
    }
}

int main() {
    int star_bitree[MAX_X] = {};
    int count[MAX_LVL] = {};

    int n, x, y;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        scanf("%d%d", &x, &y);
        ++count[Query(star_bitree, ++x)];
        Update(star_bitree, MAX_X, x, 1);
    }

    for(int i=0; i<n; ++i) {
        printf("%d\n", count[i]);
    }

    return 0;
}