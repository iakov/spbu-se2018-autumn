#include "md5.h"
#include <stdint.h>
#pragma once

long int hash(char *key){
	long int hash = algorythm_md5(key);
	return hash;
}
