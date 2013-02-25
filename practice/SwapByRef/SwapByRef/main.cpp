// #include <iostream>
#include <utility>

template<class T> inline
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

class A			// base
{
public:
    A(){m=0;n=2;};	// constructor
protected:
    int m,n;	// members
};
class B : public A	// derived
{
public:
    B(){m=1;n=3;};	// constructor
};

// template<class T> inline
// void swap(T *a, T *b)
// {
//     T tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// template<class T> inline
// void swap(T* &a, T* &b)
// {
//     T* tmp = a;
//     a = b;
//     b = tmp;
// }

// template<> inline
// void swap(void* &a, void* &b)
// {
//     void* tmp = a;
//     a = b;
//     b = tmp;
// }

int main(int argc, char** argv) {
    int var_a = 2;
    int var_b = 3;
    swap(var_a, var_b);
    int* ptra = &var_a;
    int* ptrb = &var_b;
    swap(ptra, ptrb); // compilation error

    A* ptr_a = new A;
    A* ptr_b = new B;
    swap(ptr_a, ptr_b);

    return 0;
}