#ifndef _STDH_
#define _STDH_

typedef unsigned bool;

extern const bool true;
extern const bool false;

typedef void* element_t;
typedef int (*element_cmp_fun_t)(const element_t, const element_t);

void element_swap(element_t*, element_t*);
int int_cmp(int, int);


#ifndef TRUE
#define TRUE (!0)
#endif /*TRUE*/

#ifndef FALSE
#define FALSE (0)
#endif /*FALSE*/

#endif /*_STDH_*/
