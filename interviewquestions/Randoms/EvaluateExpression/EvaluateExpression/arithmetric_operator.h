#ifndef ARITHMETIC_OPERATOR_H__
#define ARITHMETIC_OPERATOR_H__

#include <string>

// operations execute in order of precedence: the higher precedence operations execute before the lower precedence ones
enum PRECEDENCE { ZERO, ONE, TWO, THREE, FOUR, ULTIMATE };
// enum ASSOCIATIVITY { NONE, LEFT, RIGHT }; // Assume left-associative!!!
enum ARITY { UNARY, BINARY }; // only support up to binary operator for now

template<typename T>
struct Operator {
    std::string opstr;
    PRECEDENCE prec;
    ARITY arity;
    T (*opfunc)(T, T);

    T operator()(T x, T y) const { return (*opfunc)(x,y); }
};

// Supported Operator Functors:
template<typename T> typename T FunctorPlus(T x, T y) { return x + y; };
template<typename T> typename T FunctorMinus(T x, T y) { return x - y; };
template<typename T> typename T FunctorMultiply(T x, T y) { return x * y; };
template<typename T> typename T FunctorDivide(T x, T y) { return x / y; };

#endif