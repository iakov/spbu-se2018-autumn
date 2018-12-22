#include <string.h>

#include "hash.h"

typedef union tagBlock
{
    uint8_t bytes[64];
    uint32_t words[16];
} Block;

static inline uint32_t rotate( uint32_t x, uint32_t n )
{
    return (x << n | x >> (32 - n));
}

static inline uint32_t transform1( uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
                                   uint32_t x, uint32_t t, uint32_t s )
{
    a1 += (a2 & a3) | (~a2 ^ a4);
    a1 += x + t;
    a1 = rotate(a1, s);
    
    return a1 + a2;
}

static inline uint32_t transform2( uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
                                   uint32_t x, uint32_t t, uint32_t s )
{
    a1 += (a2 & a4) | (~a4 ^ a3);
    a1 += x + t;
    a1 = rotate(a1, s);

    return a1 + a2;
}

static inline uint32_t transform3( uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
                                   uint32_t x, uint32_t t, uint32_t s )
{
    a1 += a2 ^ a3 ^ a4;
    a1 += x + t;
    a1 = rotate(a1, s);

    return a1 + a2;
}

static inline uint32_t transform4( uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
                                   uint32_t x, uint32_t t, uint32_t s )
{
    a1 += a3 ^ (~a4 | a2);
    a1 += x + t;
    a1 = rotate(a1, s);

    return a1 + a2;
}

static void processBlock( Hash* hash, Block* block )
{
    uint32_t a = hash->int32[0];
    uint32_t b = hash->int32[1];
    uint32_t c = hash->int32[2];
    uint32_t d = hash->int32[3];
    
    a = transform1(a, b, c, d, block->words[0x0], 0xD76AA478, 0x07);
    d = transform1(d, a, b, c, block->words[0x1], 0xE8C7B756, 0x0C);
    c = transform1(c, d, a, b, block->words[0x2], 0x242070DB, 0x11);
    b = transform1(b, c, d, a, block->words[0x3], 0xC1BDCEEE, 0x16);
    a = transform1(a, b, c, d, block->words[0x4], 0xF57C0FAF, 0x07);
    d = transform1(d, a, b, c, block->words[0x5], 0x4787C62A, 0x0C);
    c = transform1(c, d, a, b, block->words[0x6], 0xA8304613, 0x11);
    b = transform1(b, c, d, a, block->words[0x7], 0xFD469501, 0x16);
    a = transform1(a, b, c, d, block->words[0x8], 0x698098D8, 0x07);
    d = transform1(d, a, b, c, block->words[0x9], 0x8B44F7AF, 0x0C);
    c = transform1(c, d, a, b, block->words[0xA], 0xFFFF5BB1, 0x11);
    b = transform1(b, c, d, a, block->words[0xB], 0x895CD7BE, 0x16);
    a = transform1(a, b, c, d, block->words[0xC], 0x6B901122, 0x07);
    d = transform1(d, a, b, c, block->words[0xD], 0xFD987193, 0x0C);
    c = transform1(c, d, a, b, block->words[0xE], 0xA679438E, 0x11);
    b = transform1(b, c, d, a, block->words[0xF], 0x49B40821, 0x16);
    a = transform2(a, b, c, d, block->words[0x1], 0xF61E2562, 0x05);
    d = transform2(d, a, b, c, block->words[0x6], 0xC040B340, 0x09);
    c = transform2(c, d, a, b, block->words[0xB], 0x265E5A51, 0x0E);
    b = transform2(b, c, d, a, block->words[0x0], 0xE9B6C7AA, 0x14);
    a = transform2(a, b, c, d, block->words[0x5], 0xD62F105D, 0x05);
    d = transform2(d, a, b, c, block->words[0xA], 0x02441453, 0x09);
    c = transform2(c, d, a, b, block->words[0xF], 0xD8A1E681, 0x0E);
    b = transform2(b, c, d, a, block->words[0x4], 0xE7D3FBC8, 0x14);
    a = transform2(a, b, c, d, block->words[0x9], 0x21E1CDE6, 0x05);
    d = transform2(d, a, b, c, block->words[0xE], 0xC33707D6, 0x09);
    c = transform2(c, d, a, b, block->words[0x3], 0xF4D50D87, 0x0E);
    b = transform2(b, c, d, a, block->words[0x8], 0x455A14ED, 0x14);
    a = transform2(a, b, c, d, block->words[0xD], 0xA9E3E905, 0x05);
    d = transform2(d, a, b, c, block->words[0x2], 0xFCEFA3F8, 0x09);
    c = transform2(c, d, a, b, block->words[0x7], 0x676F02D9, 0x0E);
    b = transform2(b, c, d, a, block->words[0xC], 0x8D2A4C8A, 0x14);
    a = transform3(a, b, c, d, block->words[0x5], 0xFFFA3942, 0x04);
    d = transform3(d, a, b, c, block->words[0x8], 0x8771F681, 0x0B);
    c = transform3(c, d, a, b, block->words[0xB], 0x6D9D6122, 0x10);
    b = transform3(b, c, d, a, block->words[0xE], 0xFDE5380C, 0x17);
    a = transform3(a, b, c, d, block->words[0x1], 0xA4BEEA44, 0x04);
    d = transform3(d, a, b, c, block->words[0x4], 0x4BDECFA9, 0x0B);
    c = transform3(c, d, a, b, block->words[0x7], 0xF6BB4B60, 0x10);
    b = transform3(b, c, d, a, block->words[0xA], 0xBEBFBC70, 0x17);
    a = transform3(a, b, c, d, block->words[0xD], 0x289B7EC6, 0x04);
    d = transform3(d, a, b, c, block->words[0x0], 0xEAA127FA, 0x0B);
    c = transform3(c, d, a, b, block->words[0x3], 0xD4EF3085, 0x10);
    b = transform3(b, c, d, a, block->words[0x6], 0x04881D05, 0x17);
    a = transform3(a, b, c, d, block->words[0x9], 0xD9D4D039, 0x04);
    d = transform3(d, a, b, c, block->words[0xC], 0xE6DB99E5, 0x0B);
    c = transform3(c, d, a, b, block->words[0xF], 0x1FA27CF8, 0x10);
    b = transform3(b, c, d, a, block->words[0x2], 0xC4AC5665, 0x17);
    a = transform4(a, b, c, d, block->words[0x0], 0xF4292244, 0x06);
    d = transform4(d, a, b, c, block->words[0x7], 0x432AFF97, 0x0A);
    c = transform4(c, d, a, b, block->words[0xE], 0xAB9423A7, 0x0F);
    b = transform4(b, c, d, a, block->words[0x5], 0xFC93A039, 0x15);
    a = transform4(a, b, c, d, block->words[0xC], 0x655B59C3, 0x06);
    d = transform4(d, a, b, c, block->words[0x3], 0x8F0CCC92, 0x0A);
    c = transform4(c, d, a, b, block->words[0xA], 0xFFEFF47D, 0x0F);
    b = transform4(b, c, d, a, block->words[0x1], 0x85845DD1, 0x15);
    a = transform4(a, b, c, d, block->words[0x8], 0x6FA87E4F, 0x06);
    d = transform4(d, a, b, c, block->words[0xF], 0xFE2CE6E0, 0x0A);
    c = transform4(c, d, a, b, block->words[0x6], 0xA3014314, 0x0F);
    b = transform4(b, c, d, a, block->words[0xD], 0x4E0811A1, 0x15);
    a = transform4(a, b, c, d, block->words[0x4], 0xF7537E82, 0x06);
    d = transform4(d, a, b, c, block->words[0xB], 0xBD3AF235, 0x0A);
    c = transform4(c, d, a, b, block->words[0x2], 0x2AD7D2BB, 0x0F);
    b = transform4(b, c, d, a, block->words[0x9], 0xEB86D391, 0x15);

    hash->int32[0] += a;
    hash->int32[1] += b;
    hash->int32[2] += c;
    hash->int32[3] += d;
}

Hash computeHash( const char* string, uint64_t size )
{
    uint64_t remain = size & 0x3F;
    uint64_t normalBlocksCount = size >> 6;
    uint64_t specialBlocksCount = 1 + remain / 56;

    Hash hash = {
        {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476}
    };

    Block block;

    int8_t* charPointer = (int8_t*) string;

    for (uint64_t i = 0; i < normalBlocksCount; i++)
    {
        memcpy(block.bytes, charPointer, 64);
        charPointer += 64;

        processBlock(&hash, &block);
    }

    memcpy(block.bytes, charPointer, remain);
    block.bytes[remain] = 0x80;
    memset(block.bytes + remain + 1, 0, 63 - remain);

    if (specialBlocksCount == 2)
    {
        processBlock(&hash, &block);
        memset(block.bytes, 0, sizeof(block.bytes));
    }

    block.words[14] = (uint32_t) (size << 3);
    block.words[15] = (uint32_t) (size >> 29);

    processBlock(&hash, &block);

    return hash;
}
