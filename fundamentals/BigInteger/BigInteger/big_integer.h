//////////////////////////////////////////////////////////////////////////
// Custom big integer class that support most mathematical operators
// can be converted to and from most primitive integer types.
// Notice the number itself might consume large chunk of memory and so
// "COPY" operation is constrained now, i.e.
// function input parameters use reference and not value (copy)
// Thus (-x) behave differently from naiive integer types!!! (intentional)
//////////////////////////////////////////////////////////////////////////
#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <climits>
#include <cassert>
#include <string>
#include <iostream>

namespace augment_data_structure {
//////////////////////////////////////////////////////////////////////////

template<int BUFFER_SIZE=1024>
class BigInt {
public:
    typedef unsigned char DataType;
    typedef BigInt<BUFFER_SIZE>& reference;
    typedef const BigInt<BUFFER_SIZE>& const_reference;
    static const short NUMBER_BASE = UCHAR_MAX + 1;

public:
    // Constructs zero.
    BigInt();

    // Constructors from primitive integer types
    BigInt(unsigned long  x);
    BigInt(         long  x);
    BigInt(unsigned int   x);
    BigInt(         int   x);
    BigInt(unsigned short x);
    BigInt(         short x);

    // String format output is 10 based!!!
    void ReadIn(const std::string&);
    std::string String() const;

    // Utility functions:
    int Size() { return used_; }
    void NegateSign() { sign_ = (sign_==NEGATIVE) ? NON_NEGATIVE : NEGATIVE; }
    bool IsLessThan(const_reference) const;

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
    MAG_COMPARED MagCompare(const_reference); // return true if rths data larger
    void UniAdd(const_reference);
    void UniSubtract(const_reference);
    void UniMultiplyGradeSchool(const_reference);

    // Enumeration for the sign of a BigInt.
    Sign sign_;
    int used_;
    DataType dat_[BUFFER_SIZE];
};

// template<int BUFFER_SIZE> const BigInt<BUFFER_SIZE> operator+(BigInt<BUFFER_SIZE>, const BigInt<BUFFER_SIZE>&) {
//     lfhs += rths;
//     return lfhs;
// }

// template<int BUFFER_SIZE>
// inline const BigInt<BUFFER_SIZE> operator+(BigInt<BUFFER_SIZE> lfhs, const BigInt<BUFFER_SIZE>& rths) {
//     lfhs += rths;
//     return lfhs;
// }

//////////////////////////////////////////////////////////////////////////
// Core Functions Implementation below:
//////////////////////////////////////////////////////////////////////////

template<int BUFFER_SIZE>
BigInt<BUFFER_SIZE>::BigInt()
: sign_(NON_NEGATIVE), used_(0) {
}

template<int BUFFER_SIZE>
BigInt<BUFFER_SIZE>::BigInt(int x)
: sign_(x<0 ? NEGATIVE : NON_NEGATIVE), used_(0) {
    unsigned int val = sign_==NEGATIVE ? -(x+1) : x-1;
    ++val;
    while (val>0) {
        DataType curr = val % NUMBER_BASE;
        dat_[used_++] = curr;
        val = val / NUMBER_BASE;
    }
}

template<int BUFFER_SIZE>
bool BigInt<BUFFER_SIZE>::IsLessThan(const_reference rths) const {
    if (sign_==NEGATIVE && rths.sign_==NON_NEGATIVE) return true;
    if (sign_==NON_NEGATIVE && rths.sign_==NON_NEGATIVE) return MagCompare(rths)==MAG_LESS;
    if (sign_==NEGATIVE && rths.sign_==NEGATIVE) return MagCompare(rths)==MAG_LARGER;
    return false;
}

template<int BUFFER_SIZE>
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

template<int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator-=(const_reference rths) {
    NegateSign();
    operator +=(rths);
    NegateSign();

    return *this;
}

template<int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::reference BigInt<BUFFER_SIZE>::operator*=(const_reference rths) {
    if (used_==0 || rths.used_==0) { used_=0; return *this; } // ZERO

    sign_ = (sign_==rths.sign_) ? NON_NEGATIVE : NEGATIVE;
    UniMultiplyGradeSchool(rths);

    return *this;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions:
//////////////////////////////////////////////////////////////////////////

template<int BUFFER_SIZE>
typename BigInt<BUFFER_SIZE>::MAG_COMPARED BigInt<BUFFER_SIZE>::MagCompare(const_reference rths) {
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

template<int BUFFER_SIZE>
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

template<int BUFFER_SIZE>
void BigInt<BUFFER_SIZE>::UniSubtract(const_reference rths) {
    assert(MagCompare(rths) != MAG_LESS);

    DataType curr = 0;
    DataType digit = 0;
    DataType borrow = 0;    
    for (int index = 0; index<rths.used_; ++index) {
        curr = dat_[index] - borrow;
        if (curr < rths.dat_[index]) {
            digit = curr - (UCHAR_MAX - rths.dat_[index] + 1);
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

template<int BUFFER_SIZE>
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
// string related functions
//////////////////////////////////////////////////////////////////////////
#include "big_integer_string.imph"

//////////////////////////////////////////////////////////////////////////
}

#endif