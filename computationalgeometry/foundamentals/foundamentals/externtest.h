#include <iostream>

int foo( int a, int* b)
{
    return a + *b;
}

extern int x;

void func()
{
    int y = 7;
    int r;
    r = foo( x, &y );
    printf("%d\n", r);
}	