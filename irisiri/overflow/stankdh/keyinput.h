#ifndef KEY_INPUT_H_
#define KEY_INPUT_H_

#include <windows.h>

namespace augment_window_functions
{
//////////////////////////////////////////////////////////////////////////

struct SimpleKey {
    char ch;
    bool isextended;
};

// This is a function to simplify usage of sending keys
void GenerateKey(int vk, BOOL bExtended);

inline void GenerateSimpleKey(const SimpleKey& key) {
    GenerateKey(key.ch, key.isextended);
}

//////////////////////////////////////////////////////////////////////////
}

#endif