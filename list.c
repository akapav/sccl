#include <stdlib.h>
#include "list.h"

#include "iterator.h"
#include "iterator_impl.h"

struct list_el {
  element_t el;
  struct list_el *next;
};

struct list_tag {
  struct list_el *begin;
  struct list_el *end;
};

list_t list_new(void)
{
  list_t ret = malloc(sizeof(struct list_tag));
  struct list_el *beg = malloc(sizeof(struct list_el));
  beg->el = beg->next = NULL;
  ret->begin = ret->end = beg;
  return ret;
}

static void list_delete_internal(list_t l, bool deep)
{
  struct list_el *el = l->begin;
  do {
    struct list_el *t = el->next;
    if(deep) free(el->el);
    free(el);
    el = t;
  } while(el);
  free(l);
}

void list_delete(list_t l)
{list_delete_internal(l, false);}

void list_delete_deep(list_t l)
{list_delete_internal(l, true);}

/**/
struct list_iterator {
  list_t lst;
  struct list_el* pos;
};
typedef struct list_iterator *plist_iterator;

void list_insert(list_t l, iterator_t _it, element_t el)
{
  plist_iterator it = (plist_iterator)_it->data;
  struct list_el* lel = malloc(sizeof(struct list_el));
  lel->el = el;
  lel->next = it->pos->next;
  it->pos->next = lel;
  if(it->pos == l->end) l->end = lel;
}

void list_remove(list_t l, iterator_t _it)
{
  plist_iterator it = (plist_iterator)_it->data;
  struct list_el* lel = it->pos->next;
  if(!lel) return;
  it->pos->next = lel->next;
  if(lel == l->end) l->end = it->pos;
  free(lel);
}

void list_iterator_delete(iterator_impl_t it)
{free(it);}

element_t list_iterator_get(iterator_impl_t _it)
{
  plist_iterator it = (plist_iterator)_it;
  return it->pos->next->el;
}

element_t list_iterator_set(iterator_impl_t _it, element_t el)
{
  plist_iterator it = (plist_iterator)_it;
  element_t ret = list_iterator_get(it);
  it->pos->next->el = el;
  return ret;
}

iterator_impl_t list_iterator_next(iterator_impl_t _it)
{
  plist_iterator it = (plist_iterator)_it;
  it->pos = it->pos->next;
  return it;
}

bool list_iterator_is_valid(iterator_impl_t _it)
{
  plist_iterator it = (plist_iterator)_it;
  return it->pos != NULL;
}

bool list_iterator_is_equal(iterator_impl_t _lit, iterator_impl_t _rit)
{
  plist_iterator lit = (plist_iterator)_lit;
  plist_iterator rit = (plist_iterator)_rit;
  return lit->pos == rit->pos;
}

/**/
static  plist_iterator mk_lst_iterator(list_t l, struct list_el* pos)
{
  plist_iterator ret = malloc(sizeof(struct list_iterator));
  ret->lst = l;
  ret->pos = pos;
  return ret;
}

const struct iterator_itf lst_it_vtbl = 
  {
    list_iterator_delete,
    list_iterator_get,
    list_iterator_set,
    list_iterator_next,
    list_iterator_is_valid,
    list_iterator_is_equal
  };

iterator_t list_begin(list_t l)
{
  return iterator_new
    (mk_lst_iterator(l, l->begin), &lst_it_vtbl);
}

iterator_t list_end(list_t l)
{
  return iterator_new
    (mk_lst_iterator(l, l->end), &lst_it_vtbl);
}
