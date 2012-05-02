#include "cstr_delims.h"

namespace augment_lib
{
//////////////////////////////////////////////////////////////////////////

bool IsOfSelection(const char& ch, const char* sls)
{
    while(*sls != '\0')
    {
        if (ch == *sls) return true;
        ++sls;
    }
    return false;
}

const char* NextOfSelection(const char* str, const char* toks, bool condition)
{
    while (*str != '\0')
    {
        if ( IsOfSelection(*str, toks) == condition) return str;
        ++str;
    }
    return nullptr;
}

bool PassSigDigits(const char* &s, bool& endofstr)
{
    const char* NUMERICAL_DIGITS = "0123456789";
    bool hassigdigits = s == NextOfSelection(s, NUMERICAL_DIGITS, true);
    s = NextOfSelection(s, NUMERICAL_DIGITS, false);
    if (s == nullptr || *s == '\0') {endofstr = true; return hassigdigits;}
    return hassigdigits;
}

bool PassCompactFloat(const char* &s, bool& endofstr)
{
    if (s == NextOfSelection(s, "+-", true)) ++s; // ignore plus minus sign
    if (s == nullptr || *s == '\0') {endofstr = true; return false;}

    bool hassigdigits = PassSigDigits(s, endofstr);
    if (endofstr) return hassigdigits;

    bool hasdecimals = false;
    if (s == NextOfSelection(s, ".", true)) // dot exist
    {
        ++s;
        hasdecimals = PassSigDigits(s, endofstr);
        if (endofstr) return (hassigdigits || hasdecimals);
    }

    return (hassigdigits || hasdecimals); // at least need one of them
}

bool IsValidNumber(const char *s) 
{
    s = NextOfSelection(s, " ", false); // skip spaces
    if (s == nullptr || *s == '\0') return false;

    bool endofstr = false;
    bool hassigdigits = PassCompactFloat(s, endofstr);
    if (endofstr) return hassigdigits;

    bool validexponents = true; // default is valid (zero)
    if (s == NextOfSelection(s, "eE", true)) // exp op exist
    {
        ++s;
        if (s == NextOfSelection(s, "+-", true)) ++s; // ignore plus minus sign
        if (s == nullptr || *s == '\0') return false;

        validexponents = PassSigDigits(s, endofstr);
        if (endofstr) return hassigdigits && validexponents;
    }

    s = NextOfSelection(s, " ", false);
    if (s == nullptr || *s == '\0') return hassigdigits && validexponents;

    return false;
}

//////////////////////////////////////////////////////////////////////////
}