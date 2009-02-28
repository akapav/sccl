#include "vector.h"
#include "heap.h"

struct heap_tag
{
    vector_t vec;
    element_cmp_fun_t cmpr;
    bool deep;
};

heap_t heap_new(element_cmp_fun_t cmpr, bool deep, size_t qestim)
{
    heap_t ret = malloc(sizeof(struct heap_tag));
    if(qestim) ret->vec = vector_new_ex(qestim);
    else ret->vec = vector_new();
    ret->cmpr = cmpr;
    ret->deep = deep;
    return ret;
}

void heap_delete(heap_t h)
{
    if(h->deep) vector_delete_deep(h->vec);
    else vector_delete(h->vec);
    free(h);
}

void heap_enq(heap_t h, element_t el)
{
    size_t len;
    size_t hlen;

    vector_push_back(h->vec, el);
    len = vector_size(h->vec);
    hlen = (len >> 1);

    while(hlen > 0 && h->cmpr(vector_get_element(h->vec, len - 1),
			     vector_get_element(h->vec, hlen - 1 )) > 0) {
	element_swap(vector_element_addr(h->vec, len - 1), vector_element_addr(h->vec, hlen - 1));
	len = hlen;
	hlen >>= 1;
    }
}

static element_t *step_test(vector_t v, size_t* nxt, element_cmp_fun_t cmpr)
{
    size_t ndx_chld = ((*nxt + 1) << 1);
    int diff = ndx_chld - vector_size(v);
    if(diff > 0) return 0;
    if(diff)
	if(cmpr(vector_get_element(v, ndx_chld - 1), vector_get_element(v, ndx_chld)) < 0)
	    ++ndx_chld;
    if(cmpr(vector_get_element(v, --ndx_chld), vector_get_element(v, *nxt)) > 0) {
	*nxt = ndx_chld;
	return vector_element_addr(v, ndx_chld);
    }
    return NULL;
}

void heap_deq(heap_t h)
{
    element_t *prnt = vector_element_addr(h->vec, 0);
    element_t *nxt;
    size_t ndx = 0;
    vector_set_element(h->vec, 0, (vector_get_element(h->vec, (vector_size(h->vec) - 1))));
    vector_remove(h->vec);
    while((nxt = step_test(h->vec, &ndx, h->cmpr))) {
	element_swap(prnt, nxt);
	prnt = nxt;
    }
}

element_t heap_front(heap_t h)
{
    return vector_get_element(h->vec, 0);
}

bool heap_is_empty(heap_t h)
{
    return !vector_size(h->vec);
}
