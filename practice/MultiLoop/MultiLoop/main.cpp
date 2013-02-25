#include <cstdio>

// NOTE: this problem can also be solved using loops over all elements as true/false (just loops, no recursion)
// 任意重重循环: (mitbbs version, not personal favorite lolz)
void multi_loop(int *from, int *to, int n,
    void (*callback)(const int *, int)) {
        int *i = new int[n];
        int k;
        for (k = 0; k < n; k++) {
            i[k] = from[k];
        }
        do {
            (*callback)(i, n);
            for (k = 0; k < n && ++i[k] > to[k]; k++) {
                i[k] = from[k];
            }
        } while (k < n);
        delete[] i;
}

template <typename T, typename F>
void multi_loop(const T* from, const T* to, int n, F f)
{
    T* i=new T[n];
    std::copy(from, from+n, i);
    int k;
    do {
        f(i);
        for (k = 0; k < n && ++i[k] > to[k]; i[k] = from[k], k++);
    } while (k<n);
    delete [] i;
}

void DoSth(const int* arry, int n)
{
    for (int i=n-1; i>=0; --i)
    {
        printf(" %d ", arry[i]);
    }
    printf("\n");
}

void MultiLoopRec(int loopee[], int loopor[], int idx, int size)
{
    if (idx == size) { return; }

    DoSth(loopee, size);
    for (idx=0; idx<size && (++loopee[idx])>loopor[idx]; loopee[idx]=0, ++idx);
    MultiLoopRec(loopee, loopor, idx, size);
}

void MultiLoop(int* loopee, int* loopor, int size)
{
    MultiLoopRec(loopee, loopor, 0, size);
}

int main(int argc, char** argv)
{
    int loopor[] = { 2, 2, 2, 2 };
    const int LOOP_N = sizeof(loopor)/sizeof(int);
    int loopee[LOOP_N] = {0};
    MultiLoop(loopee, loopor, LOOP_N); // recursive version
    // multi_loop(loopee, loopor, LOOP_N, DoSth);
    return 0;
}