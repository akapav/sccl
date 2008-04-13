#ifndef _LIST_
#define _LIST_

#include "stdh.h"
#include "iterator.h"

typedef struct list_tag *list_t;

list_t list_new(void);
void list_delete(list_t);
void list_delete_deep(list_t);

void list_insert(list_t, iterator_t, element_t);
void list_remove(list_t, iterator_t);

iterator_t list_begin(list_t);
iterator_t list_end(list_t);

#endif /*_LIST_*/
