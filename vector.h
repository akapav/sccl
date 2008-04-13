#ifndef _VECTOR_
#define _VECTOR_

#include <stdlib.h>
#include "stdh.h"
#include "iterator.h"

typedef struct vector_tag* vector_t;

vector_t vector_new(void);
vector_t vector_new_ex(size_t);
void vector_delete(vector_t);
void vector_delete_deep(vector_t);

element_t* vector_element_addr(vector_t, size_t);
element_t vector_get_element(vector_t, size_t);
element_t vector_set_element(vector_t, size_t, element_t);

bool vector_push_back(vector_t, element_t);
bool vector_remove(vector_t);

size_t vector_size(vector_t);
size_t vector_size_phy(vector_t);

iterator_t vector_begin(vector_t);
iterator_t vector_end(vector_t);

#endif /*_VECTOR_*/
