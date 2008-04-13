/*test proc*/

#include <stdio.h>

#include "stdh.h"
#include "list.h"
#include "vector.h"
#include "iterator.h"
#include "seq.h"

void list_push_back(list_t l, element_t el)
{
  iterator_t it = list_end(l);
  list_insert(l, it, el);
  iterator_delete(it);
}

void print_element(element_t el)
{
  printf("%d\n", (long)el);
}


void dump_vector(vector_t v)
{
  seq_for_each(vector_begin(v), vector_end(v), print_element);
  /*delete iters*/
}

void dump_list(list_t l)
{
  seq_for_each(list_begin(l), list_end(l), print_element);
  /*delete iters*/
}

int main(void)
{
  list_t l = list_new();
  vector_t v = vector_new();

  long i;


  for(i = 0; i < 10; ++i)
    list_push_back(l, (element_t)i);

  for(i = 100; i < 110; ++i)
    vector_push_back(v, (element_t)i);

  dump_list(l);
  dump_vector(v);

  list_delete(l);
  vector_delete(v);
  return 0;
}
