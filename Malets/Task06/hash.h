#pragma once

#include <stdint.h>

typedef union tagHash
{
    uint32_t int32[4];
    uint64_t int64[2];
} Hash;

extern Hash computeHash( const char* data, uint64_t dataSize );
