#ifndef _HEAP_
#define _HEAP_

#include "stdh.h"
#include <stdlib.h>

typedef struct heap_tag *heap_t;

heap_t heap_new(element_cmp_fun_t, bool deep, size_t qestim);
void heap_delete(heap_t);

void heap_enq(heap_t, element_t);
void heap_deq(heap_t);

element_t heap_front(heap_t);
bool heap_is_empty(heap_t);

#endif /*_HEAP_*/
