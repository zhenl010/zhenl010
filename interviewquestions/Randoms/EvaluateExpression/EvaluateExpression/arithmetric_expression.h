// ArithmetricExpression that can read from and write into text
// Parsing an Infix Expression with Parentheses (like ((2*4-6/3)*(3*5+8/4))-(2+3))
// Evaluate the expression using pre-defined Arithmetic operators
// 假设表达式由数字和单双目运算算符构成。
// For simplicity assume double type
#ifndef ARITHMETIC_EXPRESSION_H__
#define ARITHMETIC_EXPRESSION_H__

#include <string>
#include <vector>

// forward declaration
class ArithmetricExpression {
public:
    ArithmetricExpression(const std::string&); // construct from input text
    std::string ToString(); // Postfix Expression text
    std::string Evaluate() const; // evaluate expression and return result as string

private:
    enum InputType {
        kIsNumeric,
        kIsOperator,
        kIsFunction,
        kIsSeparator,
        kIsLeftParenthesis,
        kIsRightParenthesis,
        kIsSkip,
        kIsOther
    };

    struct ExpElement { InputType exp_type; std::string exp_str; };

    InputType GetInputType(char) const;
    void ParseInput(const std::string&, std::vector<ExpElement>&) const;
    
    std::vector<ExpElement> expression_; // Reverse Polish Notation
};

#endif