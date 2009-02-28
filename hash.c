#include "hash.h"
#include "vector.h"

typedef struct hash_element
{
    bool used;
    key_t key;
    element_t val;
} *helem_t;

struct hash_tag
{
    hash_fun_t hash;
    vector_t vect;
};

#define HNORM(val) ((val) % vector_size(h->vect))

static inline size_t find_slot(hash_t h, key_t key)
{
    size_t ndx = HNORM(h->hash(key));
    for(;;) {
		helem_t el = (helem_t)vector_get_element(h->vect, ndx);
		if(!(el->used) || el->key == key)
			return ndx;
		ndx = HNORM(ndx + 1);
    }
}

hash_t hash_new(size_t sz, hash_fun_t hash)
{
    hash_t ret = malloc(sizeof (struct hash_tag));
    int i;

    ret->hash = hash;
    ret->vect = vector_new();
    for(i = 0; i < sz; ++i) {
	helem_t el = malloc(sizeof (struct hash_element));
	el->used = false;
	el->key = el->val = NULL; /*dbg purp*/
	vector_push_back(ret->vect, el);
    }
    return ret;
}

void hash_delete(hash_t h)
{
    vector_delete_deep(h->vect);
    free(h);
}

bool hash_exists(hash_t h, key_t key)
{
    helem_t el = (helem_t)vector_get_element(h->vect, find_slot(h, key));
    return el->used;
}

element_t hash_lookup(hash_t h, key_t key)
{
    helem_t el = (helem_t)vector_get_element(h->vect, find_slot(h, key));
    return el->val;
}

void hash_set(hash_t h, key_t key, element_t val)
{
    helem_t el = (helem_t)vector_get_element(h->vect, find_slot(h, key));
    el->key = key;
    el->val = val;
    el->used = true;
}

void hash_remove(hash_t h, key_t key)
{
    helem_t el = (helem_t)vector_get_element(h->vect, find_slot(h, key));
    el->used = false;
}
