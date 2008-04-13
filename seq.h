#ifndef _SEQ_
#define _SEQ_

#include "stdh.h"
#include "iterator.h"

void seq_for_each(iterator_t begin, iterator_t end, void(*)(element_t));
element_t seq_find(iterator_t begin, iterator_t end, bool(*)(element_t), bool*);
element_t seq_reduce(iterator_t begin, iterator_t end, element_t, element_t(*)(element_t, element_t));

#endif /*_SEQ_*/
