#ifndef CSTRING_DELIMITERS_H_
#define CSTRING_DELIMITERS_H_

namespace augment_lib
{
//////////////////////////////////////////////////////////////////////////

bool IsOfSelection(const char& ch, const char* sls);

const char* NextOfSelection(const char* str, const char* toks, bool condition);

bool PassSigDigits(const char* &s, bool& endofstr);

bool PassCompactFloat(const char* &s, bool& endofstr);

bool IsValidNumber(const char *s);

//////////////////////////////////////////////////////////////////////////
}

#endif