#include "arithmetric_expression.h"
#include <cassert>
#include <stack>
#include <string>
#include <sstream>
#include "arithmetric_operator.h"

namespace {
//////////////////////////////////////////////////////////////////////////

typedef double Numeric;

// #define SIZEOF_ARRAY( a ) (sizeof( a ) / sizeof( a[ 0 ] )) 
template <typename T, size_t N>
inline size_t SizeOfArray( const T(&)[ N ] ) { return N; } // syntax here is confusingly wonky!

// Hard-coded Operators!!!
inline bool IsOperator(char c) { return c=='+' || c=='-' || c=='*' || c=='/'; }
inline bool IsFunction(char c) { return ('A'<=c && c<='Z') || ('a'<=c && c<='z'); }
inline bool IsNumber(char c) { return ('0'<=c && c<='9') || c=='.'; }
inline bool IsSeparator(char c) { return c==','; } // function parameter separators
inline bool IsLeftParenthesis(char c) { return c=='('; }
inline bool IsRightParenthesis(char c) { return c==')'; }
inline bool IsSkipChar(char c) { return c==' ' || c=='\t'; } // Whitespace is ignored.

static const Operator<Numeric> ArithOperators[] = {
    { "+", ONE, BINARY, &FunctorPlus<Numeric>     },
    { "-", ONE, BINARY, &FunctorMinus<Numeric>    },
    { "*", TWO, BINARY, &FunctorMultiply<Numeric> },
    { "/", TWO, BINARY, &FunctorDivide<Numeric>   }
};

static const Operator<Numeric>& GetOperator(std::string str) {
    for (size_t i=0; i<SizeOfArray(ArithOperators); ++i) {
        if (ArithOperators[i].opstr == str) { return ArithOperators[i]; }
    }
    return ArithOperators[SizeOfArray(ArithOperators)]; // hard throw crash
}

Numeric GetNumeric(std::string str) {
    std::stringstream strm(str);
    Numeric numeric;
    strm >> numeric;
    return numeric;
}

std::string GetString(const Numeric& num) {
    std::string str;
    std::stringstream strm;
    strm << num;
    strm >> str;
    return str;
}

//////////////////////////////////////////////////////////////////////////
}

ArithmetricExpression::ArithmetricExpression(const std::string& str) {
    // Parse and save intermediate
    std::vector<ExpElement> elements;
    ParseInput(str, elements);

    // Shunting yard
    std::stack<ExpElement> shunting_yard;
    for (size_t i=0; i<elements.size(); ++i) {
        ExpElement& element = elements[i];
        if (element.exp_type == kIsNumeric) {
            expression_.push_back(element);
        } else if (element.exp_type == kIsOperator) {
            const Operator<Numeric>& oprator = GetOperator(element.exp_str);
            while (!shunting_yard.empty() 
                && shunting_yard.top().exp_type==kIsOperator
                && GetOperator(shunting_yard.top().exp_str).prec <= oprator.prec ) {
                    expression_.push_back(shunting_yard.top());
                    shunting_yard.pop();
            }
            shunting_yard.push(element);
        } else if (element.exp_type == kIsLeftParenthesis) {
            shunting_yard.push(element);
        } else if (element.exp_type == kIsRightParenthesis) {
            while (!shunting_yard.empty() 
                && shunting_yard.top().exp_type!=kIsLeftParenthesis) {
                    expression_.push_back(shunting_yard.top());
                    shunting_yard.pop();
            }
            shunting_yard.pop();
        } else if (element.exp_type == kIsFunction) {
        } else if (element.exp_type == kIsSeparator) {
        } else if (element.exp_type == kIsOther) { // throw errors?
        } else if (element.exp_type == kIsSkip) { // do nothing
        }
    }
    
    while (!shunting_yard.empty()) {
        expression_.push_back(shunting_yard.top());
        shunting_yard.pop();
    }
}

std::string ArithmetricExpression::ToString() {
    using namespace std;
    string str;
    for (size_t i=0; i<expression_.size(); ++i) {
        str += " " + expression_[i].exp_str;
    }
    return str;
}

std::string ArithmetricExpression::Evaluate() const {
    using namespace std;
    stack<ExpElement> elements;
    for (size_t i=0; i<expression_.size(); ++i) {
        const ExpElement& curr = expression_[i];
        if (curr.exp_type == kIsNumeric) {
            elements.push(curr);
        } if (curr.exp_type == kIsOperator) {
            Numeric numB = GetNumeric(elements.top().exp_str);
            elements.pop();
            Numeric numA = GetNumeric(elements.top().exp_str);
            elements.pop();
            const Operator<Numeric>& oprator = GetOperator(curr.exp_str);
            Numeric result = oprator(numA, numB);
            ExpElement elem = { kIsNumeric, GetString(result) };
            elements.push(elem);
        }
    }
    return elements.top().exp_str;
}

inline ArithmetricExpression::InputType ArithmetricExpression::GetInputType(char c) const {
    if (IsNumber(c))    return kIsNumeric;
    if (IsOperator(c))  return kIsOperator;
    if (IsFunction(c))  return kIsFunction;
    if (IsSeparator(c)) return kIsSeparator;
    if (IsLeftParenthesis(c)) return kIsLeftParenthesis;
    if (IsRightParenthesis(c)) return kIsRightParenthesis;
    if (IsSkipChar(c))  return kIsSkip;
    return kIsOther;
}

void ArithmetricExpression::ParseInput(const std::string& str, std::vector<ExpElement>& elements) const {
    if (str.empty()) return;

    assert(GetInputType(str[0])!=kIsOther);
    std::string curr_str(1,str[0]);
    InputType curr_type = GetInputType(str[0]);
    for (size_t i=1; i<str.size(); ++i) {
        assert(GetInputType(str[i])!=kIsOther);
        if (curr_type==kIsLeftParenthesis || curr_type==kIsRightParenthesis || GetInputType(str[i])!=curr_type) {
            ExpElement element = { curr_type, curr_str };
            elements.push_back(element);
            curr_type = GetInputType(str[i]);
            curr_str = str[i];
        } else {
            curr_str += str[i];
        }
    }

    if (!curr_str.empty()) {
        ExpElement element = { curr_type, curr_str };
        elements.push_back(element);
    }
}
