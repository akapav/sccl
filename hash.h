#ifndef _HASH_
#define _HASH_

#include "stdh.h"
#include <stdlib.h>

typedef element_t key_t;

typedef size_t(*hash_fun_t)(key_t);
typedef struct hash_tag* hash_t;

hash_t hash_new(size_t sz, hash_fun_t hash);
void hash_delete(hash_t h);
bool hash_exists(hash_t h, key_t key);
element_t hash_lookup(hash_t h, key_t key);
void hash_set(hash_t h, key_t key, element_t val);
void hash_remove(hash_t h, key_t key);

#endif /*_HASH_*/
