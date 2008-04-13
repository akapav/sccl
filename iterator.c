#include "iterator.h"
#include "iterator_impl.h"

#include <stdlib.h>

iterator_t iterator_new(void *data, const struct iterator_itf* vptr)
{
  iterator_t ret = malloc(sizeof(struct iterator_tag));
  ret->data = data;
  ret->vptr = vptr;
  return ret;
}

void iterator_delete(iterator_t it)
{
  it->vptr->delete(it->data);
  free(it);
}

element_t iterator_get(iterator_t it)
{return it->vptr->get(it->data);}

element_t iterator_set(iterator_t it, element_t el)
{return it->vptr->set(it->data, el);}

iterator_t iterator_next(iterator_t it)
{
  it->data = it->vptr->next(it->data);
  return it;
}

bool iterator_is_valid(iterator_t it)
{return it->vptr->is_valid(it->data);}

bool iterator_is_equal(iterator_t lit, iterator_t rit)
{return lit->vptr->is_equal(lit->data, rit->data);}
