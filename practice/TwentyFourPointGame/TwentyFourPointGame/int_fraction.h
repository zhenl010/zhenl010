#ifndef INT_FRACTION_H_
#define INT_FRACTION_H_

#include <iostream>

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

class IntFraction
{
public:
    IntFraction(int x, int y) : numerator_(x), denominator_(y) {}
    explicit IntFraction(int x) : numerator_(x), denominator_(1) {}

    bool IsValidDivide() { return denominator_ != 0; }
    void Simplify();
    int Numerator() const { return numerator_; }
    int Denominator() const { return denominator_; }

    bool operator==(const IntFraction& rhs) { return numerator_==rhs.numerator_ && denominator_ == rhs.denominator_; }
    bool operator!=(const IntFraction& rhs) { return !(*this == rhs); }

    friend std::ostream& operator<<(std::ostream& osm, IntFraction& opf)
    {
        opf.Simplify();
        osm << opf.Numerator();
        return osm;
    }

private:
    int numerator_;
    int denominator_;
};

class OpFunctor
{
public:
    virtual IntFraction operator()(const IntFraction&, const IntFraction&) = 0;
    virtual char Char() const = 0;

    friend std::ostream& operator<<(std::ostream& osm, const OpFunctor& opf)
    {
        osm << opf.Char();
        return osm;
    }
};

class OpPlus : public OpFunctor
{
public:
    IntFraction operator()(const IntFraction& x, const IntFraction& y)
    {
        int xn = x.Numerator();
        int xd = x.Denominator();
        int yn = y.Numerator();
        int yd = y.Denominator();
        return IntFraction(xn*yd+xd*yn, xd*yd);
    }

    char Char() const { return '+'; }
};

class OpMinus : public OpFunctor
{
public:
    IntFraction operator()(const IntFraction& x, const IntFraction& y)
    {
        int xn = x.Numerator();
        int xd = x.Denominator();
        int yn = y.Numerator();
        int yd = y.Denominator();
        return IntFraction(xn*yd-xd*yn, xd*yd);
    }

    char Char() const { return '-'; }
};

class OpMultiply : public OpFunctor
{
public:
    IntFraction operator()(const IntFraction& x, const IntFraction& y)
    {
        int xn = x.Numerator();
        int xd = x.Denominator();
        int yn = y.Numerator();
        int yd = y.Denominator();
        return IntFraction(xn*yn, xd*yd);
    }

    char Char() const { return '*'; }
};

class OpDivide : public OpFunctor
{
public:
    IntFraction operator()(const IntFraction& x, const IntFraction& y)
    {
        int xn = x.Numerator();
        int xd = x.Denominator();
        int yn = y.Numerator();
        int yd = y.Denominator();
        return IntFraction(xn*yd, xd*yn);
    }

    char Char() const { return '/'; }
};

//////////////////////////////////////////////////////////////////////////
}

#endif