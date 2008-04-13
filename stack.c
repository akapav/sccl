#include "stack.h"
#include "vector.h"
#include <stdlib.h>

struct stack_tag
{
    vector_t vect;
};

stack_t stack_new(void)
{
    stack_t ret = malloc(sizeof(struct stack_tag));
    ret->vect = vector_new();
    return ret;
}

void stack_delete(stack_t s)
{
    vector_delete(s->vect);
    free(s);
}

void stack_push(stack_t s, element_t el)
{
    vector_push_back(s->vect, el);
}

element_t stack_pop(stack_t s)
{
    element_t ret = stack_top(s);
    vector_remove(s->vect);
    return ret;
}

element_t stack_top(stack_t s)
{
    return vector_get_element(s->vect, vector_size(s->vect) - 1);
}

bool stack_is_empty(stack_t s)
{
    return !vector_size(s->vect);
}
