#ifndef _ITERATOR_
#define _ITERATOR_

#include "stdh.h"

typedef struct iterator_tag* iterator_t;

void iterator_delete(iterator_t);

element_t iterator_get(iterator_t);
element_t iterator_set(iterator_t, element_t);

iterator_t iterator_next(iterator_t);

bool iterator_is_valid(iterator_t);
bool iterator_is_equal(iterator_t, iterator_t);

#endif /*_ITERATOR_*/
