// 给一个表达式，计算返回值，不带括号. 例子:
//     "7-12/6"
//     "1000-5*6/3*2+1"
#include <iostream>
#include <string>
#include "arithmetric_expression.h"

int main(int argc, char** argv) {
    using namespace std;
    string arith_str = "5 + ((1 + 2) * 4) - 3";
    ArithmetricExpression expression(arith_str);
    string expression_postfix_str = expression.ToString();
    string result = expression.Evaluate();

    return 0;
}