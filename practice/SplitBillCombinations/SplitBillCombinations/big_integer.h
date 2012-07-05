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

template<unsigned int BUFFER_SIZE=1024>
class BigInt {
public:
    typedef unsigned char DataType; // UNDERLINING DATA TYPE
    typedef BigInt<BUFFER_SIZE>& reference;
    typedef const BigInt<BUFFER_SIZE>& const_reference;
    static const unsigned short NUMBER_BASE = UCHAR_MAX + 1;
    static const unsigned short NUMBER_BASE_HALF = NUMBER_BASE / 2;
    static const unsigned short NUMBER_BASE_BITS = sizeof(DataType) << 3;
    static const unsigned long long int DIVIDE_BASE_CONST = ULONG_MAX;
    static const unsigned int DIVIDE_SHIFT_CONST = 4;
    static const unsigned int DIVIDE_BASECASE_CONST = 3; // Used by RecursiveDivide

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
    bool IsNegative() const { return sign_==NEGATIVE; }
    void NegateSign() { sign_ = IsNegative() ? NON_NEGATIVE : NEGATIVE; }
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
    // Non-Member arithmetic operators (allow implicit conversion):
    //////////////////////////////////////////////////////////////////////////
    #include "big_integer_nonmembers.imph"

    //////////////////////////////////////////////////////////////////////////
    // Big Integer IO:
    //////////////////////////////////////////////////////////////////////////
    #include "big_integer_io.imph"

private:
    enum Sign { NEGATIVE = -1, NON_NEGATIVE = 1 };
    enum MAG_COMPARED { MAG_LESS = -1, MAG_EQUAL = 0, MAG_LARGER = 1 };

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
    void UniMultiplyGradeSchool(const_reference);
    // Divisions
    void UniBaseDivide(const_reference);
    void UniRecursiveDivide(const_reference);
    void UniRecursiveDivideSpecial(const_reference); // (A.ByteSize - B.ByteSize) <= B.ByteSize
    void UniNewtonDivide(const_reference); ///@TODO: heavy optimize

    // Enumeration for the sign of a BigInt.
    Sign sign_;
    int used_;
    DataType dat_[BUFFER_SIZE];
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
    if (IsNegative() && rths.sign_==NON_NEGATIVE) return true;
    if (sign_==NON_NEGATIVE && rths.sign_==NON_NEGATIVE) return MagCompare(rths)==MAG_LESS;
    if (IsNegative() && rths.IsNegative()) return MagCompare(rths)==MAG_LARGER;
    return false;
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::ShiftLeft(unsigned int num) {  // Logical shift
    if (used_ == 0) return; // nothing to do if ZERO

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
            dat_[0] = 0;
            used_ = 1;
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
    if (used_==0 || rths.used_==0) { used_=0; return *this; } // ZERO

    sign_ = (sign_==rths.sign_) ? NON_NEGATIVE : NEGATIVE;
    UniMultiplyGradeSchool(rths);

    return *this;
}

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator/=(const_reference rths) {
    sign_ = (sign_==rths.sign_) ? NON_NEGATIVE : NEGATIVE;
    // UniBaseDivide(rths);
    UniRecursiveDivide(rths);
    // UniNewtonDivide(rths);

    return *this;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions:
//////////////////////////////////////////////////////////////////////////

template<unsigned int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::MAG_COMPARED BigInt<BUFFER_SIZE>::MagCompare(const_reference rths) const {
    if (used_ < rths.used_) return MAG_LESS;
    if (rths.used_ < used_) return MAG_LARGER;
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
        DataType curr = val % NUMBER_BASE;
        dat_[used_++] = curr;
        val = val / NUMBER_BASE;
    }
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::UniAdd(const_reference rths) {
    unsigned short cursum = 0;
    DataType digit = 0;
    DataType carry = 0;
    int index = 0;
    if (rths.used_ > used_) {
        for (; index<used_; ++index) {
            cursum = carry + rths.dat_[index] + dat_[index];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[index] = digit;
        }
        for (; carry>0 && index<rths.used_; ++index) {
            cursum = carry + rths.dat_[index];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[index] = digit;
        }
        if (carry>0) {
            dat_[index++] = carry;
            used_ = index;
        } else {
            memcpy (&dat_[index], &rths.dat_[index], rths.used_-index);
            used_ = rths.used_;
        }
    } else { // (curr.size() <= numstr.size())
        for (; index<rths.used_; ++index) {
            cursum = carry + rths.dat_[index] + dat_[index];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[index] = digit;
        }
        for (; carry>0 && index<used_; ++index) {
            cursum = carry + dat_[index];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[index] = digit;
        }
        if (carry>0) {
            dat_[index++] = carry;
            used_ = index;
        }
    }
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::UniSubtract(const_reference rths) {
    assert(MagCompare(rths) != MAG_LESS);

    short int curr = 0;
    DataType digit = 0;
    DataType borrow = 0;    
    for (int index = 0; index<rths.used_; ++index) {
        curr = dat_[index] - borrow;
        if (curr < rths.dat_[index]) {
            digit = curr + (UCHAR_MAX - rths.dat_[index] + 1);
            borrow = 1;
        } else {
            digit = curr - rths.dat_[index];
            borrow = 0;
        }
        dat_[index] = digit;
    }
    if (borrow>0) { dat_[rths.used_] -= borrow; }

    for (int i=used_-1; i>=0 && dat_[i]==0; --i, --used_) {}
}

template<unsigned int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::UniMultiplyGradeSchool(const_reference rths) {
    // if (used_==0 || rths.used_==0) { used_=0; return; }
    BigInt<BUFFER_SIZE> lfhs(*this);
    memset(&dat_[0], 0, BUFFER_SIZE);

    unsigned short cursum = 0;
    DataType digit = 0;
    DataType carry = 0;
    for(int i=0; i<lfhs.used_; ++i) {
        int idx = i; // result array index
        for(int j=0; j<rths.used_; ++j, ++idx) {
            // digit = carry+(numone[i]-'0')*(numtwo[j]-'0') + number[idx]-'0';
            cursum = carry+(lfhs.dat_[i])*(rths.dat_[j]) + dat_[idx];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[idx] = digit;
        }

        while (carry>0) {
            cursum = carry + dat_[idx];
            carry = cursum / NUMBER_BASE;
            digit = cursum % NUMBER_BASE;
            dat_[idx] = digit;
            ++idx;
        }
        used_ = idx;
    }
}

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