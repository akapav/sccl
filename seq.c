#include "seq.h"
#include <stdlib.h>

void seq_for_each(iterator_t begin, iterator_t end, void(*fun)(element_t))
{
  iterator_t it;

  for(it = begin; !iterator_is_equal(it, end); it = iterator_next(it))
    fun(iterator_get(it));

  /*iterator_delete(begin);
    iterator_delete(end)*/
}

element_t seq_find(iterator_t begin, iterator_t end, bool(*pred)(element_t), bool *succ)
{
  iterator_t it;
  if(succ) *succ = false;

  for(it = begin; !iterator_is_equal(it, end); it = iterator_next(it))
    if(pred(iterator_get(it))) {
      if(succ) *succ = true;
      return iterator_get(it);
    }

  return NULL;
}

element_t seq_reduce(iterator_t begin, iterator_t end, element_t start, element_t(*op)(element_t, element_t))
{
  iterator_t it;
  element_t ret = start;

  for(it = begin; !iterator_is_equal(it, end);
      ret = op(iterator_get(it), ret), it = iterator_next(it));
  return ret;
}
