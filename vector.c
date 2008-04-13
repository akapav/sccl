#include <stdlib.h>
#include "vector.h"

#include "iterator.h"
#include "iterator_impl.h"

#define VECTOR_INIT_SIZE 10
struct vector_tag
{
    element_t *arr;
    size_t logical, phy;
    size_t reserve;
};

static vector_t vector_new_internal(size_t res, size_t init)
{
    vector_t ret = malloc(sizeof (struct vector_tag));
    ret->arr = malloc(sizeof(element_t) * (ret->phy = init));
    ret->logical = 0;
    ret->reserve = res;
    return ret;
}

vector_t vector_new(void)
{
	return vector_new_internal(0, VECTOR_INIT_SIZE);
}

vector_t vector_new_ex(size_t reserve)
{
	return vector_new_internal(reserve, reserve);
}

void vector_delete(vector_t v)
{
    free(v->arr);
    free(v);
}

static void vector_for_each(vector_t v, void(*fun)(element_t)) /*todo*/
{
  size_t i;
  for(i = 0; i < vector_size(v); ++i)
    fun(vector_get_element(v, i));
}

void vector_delete_deep(vector_t v)
{
    vector_for_each(v, free);
    vector_delete(v);
}

element_t* vector_element_addr(vector_t v, size_t ndx)
{
    return (v->arr) + ndx;
}

element_t vector_get_element(vector_t v, size_t ndx)
{
    return *vector_element_addr(v, ndx);
}

element_t vector_set_element(vector_t v, size_t ndx, element_t el)
{
    element_t ret = *vector_element_addr(v, ndx);
    *vector_element_addr(v, ndx) = el;
    return ret;
}

bool vector_push_back(vector_t v, element_t el)
{
    bool ret = ((v->logical + 1)== v->phy);
    if(ret) v->arr = realloc(v->arr, sizeof(element_t) * (v->phy <<= 1));
    v->arr[v->logical++] = el;
    return ret;
}

bool vector_remove(vector_t v)
{
    bool ret = (--v->logical <= (v->phy >> 2)) && ((v->phy >> 1) >= v->reserve);
    if(ret) v->arr = realloc(v->arr, sizeof(element_t) * (v->phy >>= 1));
    return ret;
}

size_t vector_size(vector_t v)
{
    return v->logical;
}

size_t vector_size_phy(vector_t v)
{
    return v->phy;
}

/**/
struct vector_iterator {
  vector_t vect;
  size_t ndx;
};
typedef struct vector_iterator *pvector_iterator;

void vector_iterator_delete(iterator_impl_t it)
{free(it);}

element_t vector_iterator_get(iterator_impl_t _it)
{
  pvector_iterator it = (pvector_iterator)_it;
  return vector_get_element(it->vect, it->ndx);
}

element_t vector_iterator_set(iterator_impl_t _it, element_t el)
{
  pvector_iterator it = (pvector_iterator)_it;
  return vector_set_element(it->vect, it->ndx, el);
}

iterator_impl_t vector_iterator_next(iterator_impl_t _it)
{
  pvector_iterator it = (pvector_iterator)_it;
  ++it->ndx;
  return it;
}

bool vector_iterator_is_valid(iterator_impl_t _it)
{
  pvector_iterator it = (pvector_iterator)_it;
  return it->ndx >= 0 && it->ndx < vector_size(it->vect);
}

bool vector_iterator_is_equal(iterator_impl_t _lit, iterator_impl_t _rit)
{
  pvector_iterator lit = (pvector_iterator)_lit;
  pvector_iterator rit = (pvector_iterator)_rit;
  return lit->ndx == rit->ndx;
}

/**/
static pvector_iterator mk_vect_iterator(vector_t v, size_t ndx)
{
  pvector_iterator ret = malloc(sizeof(struct vector_iterator));
  ret->vect = v;
  ret->ndx = ndx;
  return ret;
}

const struct iterator_itf vect_it_vtbl = 
  {
    vector_iterator_delete,
    vector_iterator_get,
    vector_iterator_set,
    vector_iterator_next,
    vector_iterator_is_valid,
    vector_iterator_is_equal
  };

iterator_t vector_begin(vector_t v)
{
  return iterator_new
    (mk_vect_iterator(v, 0), &vect_it_vtbl);

}

iterator_t vector_end(vector_t v)
{
  return iterator_new
    (mk_vect_iterator(v, vector_size(v)), &vect_it_vtbl);
}

#undef VECTOR_INIT_SIZE
