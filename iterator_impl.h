#ifndef _ITERATOR_IMPL_
#define _ITERATOR_IMPL_

#include "stdh.h"
#include "iterator.h"

typedef void* iterator_impl_t;
struct iterator_itf
{
  void (*delete)(iterator_impl_t);
  element_t (*get)(iterator_impl_t);
  element_t (*set)(iterator_impl_t, element_t);
  iterator_impl_t (*next)(iterator_impl_t);
  bool (*is_valid)(iterator_impl_t);
  bool (*is_equal)(iterator_impl_t, iterator_impl_t);
};

iterator_t iterator_new(void *data, const struct iterator_itf* vptr);

struct iterator_tag
{
  void *data;
  const struct iterator_itf* vptr;
};

#endif /*_ITERATOR_IMPL_*/
