#ifndef HASH_MD5_H
#define HASH_MD5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest);

#endif //HASH_MD5_H

