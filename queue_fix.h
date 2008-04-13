#ifndef _QUEUE_FIX_
#define _QUEUE_FIX_

#include "stdh.h"
#include <stdlib.h>

typedef struct queue_fix_tag* queue_fix_t;

queue_fix_t queue_fix_new(size_t);
void queue_fix_delete(queue_fix_t);

void queue_fix_enque(queue_fix_t, element_t);
element_t queue_fix_dequeue(queue_fix_t);
element_t queue_fix_front(queue_fix_t);

bool queue_fix_is_full(queue_fix_t);
bool queue_fix_is_empty(queue_fix_t);

size_t queue_fix_size(queue_fix_t);
size_t queue_fix_size_phy(queue_fix_t);

/*debug iface*/
void queue_fix_dump(queue_fix_t q, const char *fmt);

#endif /*_QUEUE_FIX_*/
