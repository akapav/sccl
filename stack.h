#ifndef _STACK_
#define _STACK_

#include "stdh.h"

typedef struct stack_tag* stack_t;

stack_t stack_new(void);
void stack_delete(stack_t);

void stack_push(stack_t, element_t);
element_t stack_pop(stack_t);
element_t stack_top(stack_t);

bool stack_is_empty(stack_t);

#endif /*_STACK_*/
