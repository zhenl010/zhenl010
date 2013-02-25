//////////////////////////////////////////////////////////////////////////
// Custom big integer class that support most mathematical operators
// can be converted to and from most primitive integer types.
// Notice the number itself might consume large chunk of memory and so
// "COPY" operation is constrained now, i.e.
// function input parameters use reference and not value (copy)
// Thus (-x) behave differently from naiive integer types!!! (intentional)
//////////////////////////////////////////////////////////////////////////
// UNDERLINING DATA TYPE: unsigned char (strong assumption in this implementation)
//////////////////////////////////////////////////////////////////////////
#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <climits>
#include <cassert>
#include <string>
#include <iostream>

namespace augment_data_structure {
//////////////////////////////////////////////////////////////////////////

inline unsigned int ilog2(unsigned int x) 
{
    register unsigned int l=0;
    if(x >= 1<<16) { x>>=16; l|=16; }
    if(x >= 1<<8) { x>>=8; l|=8; }
    if(x >= 1<<4) { x>>=4; l|=4; }
    if(x >= 1<<2) { x>>=2; l|=2; }
    if(x >= 1<<1) l|=1;
    return l;
}

// http://www.hackersdelight.org/divcMore.pdf
const  unsigned short DivideByThree(unsigned short lfhs) {
    unsigned short quodient = (lfhs>>2) + (lfhs>>4);
    quodient = quodient + (quodient >> 4);
    quodient = quodient + (quodient >> 8);
    return quodient + (11*(lfhs - quodient*3) >> 5);
}

template<unsigned int BUFFER_SIZE=1024>
class BigInt {
public:
    typedef unsigned char DataType; // UNDERLINING DATA TYPE
    typedef BigInt<BUFFER_SIZE>& reference;
    typedef const BigInt<BUFFER_SIZE>& const_reference;
    static const unsigned short NUMBER_BASE = UCHAR_MAX + 1;
    static const unsigned short NUMBER_BASE_HALF = NUMBER_BASE / 2;
    static const unsigned short NUMBER_BASE_BITS = sizeof(DataType) << 3;
    static const int MUL_THRESHOLD_BASE = 3;
    static const int MUL_THRESHOLD_KARATSUBA = 64;
    static const int MUL_THRESHOLD_TOOMCOOK = 6400;
    static const unsigned long long int DIVIDE_BASE_CONST = ULONG_MAX;
    static const unsigned int DIVIDE_SHIFT_CONST = 4;
    static const unsigned int DIVIDE_BASECASE_CONST = 4; // Used by RecursiveDivide

public:
    // Constructs zero.
    BigInt();

    // Constructors from primitive integer types
    BigInt(unsigned long long int x);
    BigInt(         long long int x);
    BigInt(unsigned int   x);
    BigInt(         int   x);
    BigInt(unsigned short x);
    BigInt(         short x);

    // String format output is 10 based!!!
    void ReadIn(const std::string&);
    std::string String() const;

    // Utility functions:
    void SetAsZero() { used_=0; }
    bool IsZero() const { return used_==0; }
    bool IsNegative() const { return sign_==NEGATIVE && (!IsZero()); } // ZERO is non-negative
    void NegateSign() { sign_ = IsZero() ? NON_NEGATIVE : (IsNegative() ? NON_NEGATIVE : NEGATIVE); }
    bool IsLessThan(const_reference) const;
    int ByteSize() const { return used_; }
    void ByteResize(unsigned int k) { used_ = (used_>(int)k) ? (int)k : used_; }
    void ShiftLeft(unsigned int); // Logical shift
    void ShiftRight(unsigned int); // Logical shift

    // Arithmetic
    reference operator +=(const_reference);
    reference operator -=(const_reference);
    reference operator *=(const_reference);
    reference operator /=(const_reference);

    // Incremental/Decremental
    void operator ++(   );
    void operator ++(int);
    void operator --(   );
    void operator --(int);

public:
    //////////////////////////////////////////////////////////////////////////
    // Non-Member IO and arithmetic friend operators (allow implicit conversion):
    //////////////////////////////////////////////////////////////////////////
    #include "big_integer_nonmembers.imph"

private:
    enum Sign { NEGATIVE, NON_NEGATIVE };
    enum MAG_COMPARED { MAG_LESS, MAG_EQUAL, MAG_LARGER };

    // String related Helper functions
    static std::string ToString(DataType x);
    static std::string StringNumPlus(const std::string&, const std::string&); // NON-NEGATIVES
    static std::string StringNumMultiply(const std::string&, const std::string&); // NON-NEGATIVES
    static DataType StringNumModule(std::string&); // NON-NEGATIVES and const denominator 256

    // Arithmetics Helpers
    MAG_COMPARED MagCompare(const_reference) const; // return true if rths data larger
    void ConstructBuffer(unsigned long long int);
    void UniAdd(const_reference);
    void UniSubtract(const_reference);
    // Multiplications
    void UniMultiply(const_reference);
    void UniMultiplyGradeSchool(const_reference);
    void UniMultiplyToomCook2(const_reference); // Karatsuba
    void UniMultiplyToomCook2p5(const_reference);
    unsigned int UniToomCook2p5Inter(BigInt<BUFFER_SIZE> mul_poly[4], const BigInt<BUFFER_SIZE>&, const BigInt<BUFFER_SIZE>&);
    void UniToomCook2p5CoeffA(BigInt<BUFFER_SIZE> coeffs[4], const BigInt<BUFFER_SIZE>&, unsigned int);
    void UniToomCook2p5CoeffB(BigInt<BUFFER_SIZE> coeffs[4], const BigInt<BUFFER_SIZE>&, unsigned int);
    void UniMultiplyToomCook3(const_reference);
    unsigned int UniToomCook3Inter(BigInt<BUFFER_SIZE> mul_poly[5], const BigInt<BUFFER_SIZE>&, const BigInt<BUFFER_SIZE>&);
    void UniToomCook3Coeff(BigInt<BUFFER_SIZE> coeffs[5], const BigInt<BUFFER_SIZE>&, unsigned int);
    void UniMultiplySchonhageStrassen(const_reference);
    // Divisions
    void UniDivide(const_reference);
    void UniBaseDivide(const_reference);
    void UniRecursiveDivide(const_reference);
    void UniRecursiveDivideSpecial(const_reference); // (A.ByteSize - B.ByteSize) <= B.ByteSize
    void UniNewtonDivide(const_reference); ///@TODO: heavy optimize

    // Enumeration for the sign of a BigInt.
    Sign sign_;
    int used_;
    DataType dat_[BUFFER_SIZE];

public:
    void UniExactDivByTwo();
    void UniExactDivByThree();
};

//////////////////////////////////////////////////////////////////////////
// Core Functions Implementation below:
//////////////////////////////////////////////////////////////////////////

template<unsigned int BUFFER_SIZE>
BigInt<BUFFER_SIZE>::BigInt()
: sign_(NON_NEGATIVE), used_(0) {
}

template<unsigned int BUFFER_SIZE>
BigInt<BUFFER_SIZE>::BigInt(unsigned long long int x)
: sign_(NON_NEGATIVE), used_(0) {
    ConstructBuffer(x);
}

template<unsigned int BUFFER_SIZE>
BigInt<BUFFER_SIZE>::BigInt(int x)
: sign_(x<0 ? NEGATIVE : NON_NEGATIVE), used_(0) {
    unsigned long long int val = IsNegative() ? -(x+1) : x-1;
    ++val;
    ConstructBuffer(val);
}

template<unsigned int BUFFER_SIZE>
bool BigInt<BUFFER_SIZE>::IsLessThan(const_reference rths) const {
    if (IsNegative() && (!rths.IsNegative())) return true;
    if (IsNegative() && rths.IsNegative()) return MagCompare(rths)==MAG_LARGER;
    if ((!IsNegative()) && (!rths.IsNegative())) return MagCompare(rths)==MAG_LESS;
    return false;
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::ShiftLeft(unsigned int num) {  // Logical shift
    if (IsZero()) return; // nothing to do if ZERO

    assert(used_+num <= BUFFER_SIZE); // LOSING ACCURACY not ALLOWED!!!
    memmove(dat_+num, dat_, used_);
    memset(dat_, '\0', num);
    used_ += num;
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::ShiftRight(unsigned int num) { // Logical shift
    if (num < (unsigned int)used_) {
        used_ -= num;
        memmove(dat_, dat_+num, used_);
    } else {
        used_ = 0;
    }
}

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator+=(const_reference rths) {
    if (sign_ == rths.sign_) {
        UniAdd(rths);
    } else {
        MAG_COMPARED comp = MagCompare(rths);
        switch (comp) {
        case MAG_EQUAL:
            sign_ = NON_NEGATIVE;
            used_ = 0;
            break;
        case MAG_LARGER:
            UniSubtract(rths);
            break;
        case MAG_LESS:
            BigInt<BUFFER_SIZE> asw = rths;
            asw.UniSubtract(*this);
            operator =(asw);
            sign_ = rths.sign_;
            break;
        }
    }

    return *this;
}

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator-=(const_reference rths) {
    NegateSign();
    operator +=(rths);
    NegateSign();

    return *this;
}

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator*=(const_reference rths) {
    if (ByteSize()==0 || rths.ByteSize()==0) { SetAsZero(); return *this; } // ZERO

    sign_ = (sign_==rths.sign_) ? NON_NEGATIVE : NEGATIVE;
    UniMultiply(rths);

    return *this;
}

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator/=(const_reference rths) {
    Sign numsign = (sign_==rths.sign_) ? NON_NEGATIVE : NEGATIVE;
    if (sign_ != NON_NEGATIVE) { sign_ = NON_NEGATIVE; }
    if (rths.IsNegative()) {
        UniDivide(-rths);
    } else {
        UniDivide(rths);
    }
    sign_ = numsign;
    return *this;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions:
//////////////////////////////////////////////////////////////////////////

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::MAG_COMPARED BigInt<BUFFER_SIZE>::MagCompare(const_reference rths) const {
    if (ByteSize() < rths.ByteSize()) return MAG_LESS;
    if (rths.ByteSize() < ByteSize()) return MAG_LARGER;
    for (int i=used_-1; i>=0; --i) {
        if (dat_[i]<rths.dat_[i]) {
            return MAG_LESS;
        } else if (rths.dat_[i] < dat_[i]) {
            return MAG_LARGER;
        }
    }
    return MAG_EQUAL;
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::ConstructBuffer(unsigned long long int val) {
    while (val>0) {
        DataType curr = val & UCHAR_MAX; //  % NUMBER_BASE;
        dat_[used_++] = curr;
        val = val >> NUMBER_BASE_BITS; // / NUMBER_BASE;
    }
}

//////////////////////////////////////////////////////////////////////////
// unsigned multiplication functions
//////////////////////////////////////////////////////////////////////////
#include "big_integer_addition_substractions.imph"

//////////////////////////////////////////////////////////////////////////
// unsigned multiplication functions
//////////////////////////////////////////////////////////////////////////
#include "big_integer_multiplications.imph"

//////////////////////////////////////////////////////////////////////////
// unsigned division functions
//////////////////////////////////////////////////////////////////////////
#include "big_integer_divisions.imph"

//////////////////////////////////////////////////////////////////////////
// string related functions
//////////////////////////////////////////////////////////////////////////
#include "big_integer_string.imph"

//////////////////////////////////////////////////////////////////////////
}

#endif