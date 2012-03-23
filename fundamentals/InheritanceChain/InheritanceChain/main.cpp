#include <iostream>

class Base
{
public:
    int value_one_;

};

class Derived : public Base
{
public:
    double value_two_;


};

int main(int argc, char** argv)
{
    Base one;

    Derived two;

    Base* ptr_one = &one;
    Base* ptr_two = &two;

    return 0;
}