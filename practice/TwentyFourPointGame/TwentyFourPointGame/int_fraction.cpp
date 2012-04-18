#include "int_fraction.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

void IntFraction::Simplify()
{
    if (IsValidDivide() != true)
    {
        return; // DO NOTHING if divide by ZERO
    }

    if (numerator_ % denominator_ == 0)
    {
        numerator_ = numerator_ / denominator_;
        denominator_ = 1;
    }
}

//////////////////////////////////////////////////////////////////////////
}