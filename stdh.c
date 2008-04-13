#include "stdh.h"

const bool false = 0;
const bool true = !0;

void element_swap(element_t *ls, element_t *rs)
{
    element_t t = *ls;
    *ls = *rs;
    *rs = t;
}

int int_cmp(int ls, int rs)
{
    return rs - ls;
}
