#include "queue_fix.h"

struct queue_fix_tag
{
  element_t *arr;
  size_t front, end;
  size_t size;
};

#define QINC(val) (q -> val = (++ q-> val) % q->size)

queue_fix_t queue_fix_new(size_t size)
{
  queue_fix_t ret = malloc(sizeof(struct queue_fix_tag));
  ret->arr = malloc((ret->size = size) * sizeof(element_t));
  ret->front = ret->end = 0;
  return ret;
} 

void queue_fix_delete(queue_fix_t q)
{
  free(q->arr);
  free(q);
}

void queue_fix_enque(queue_fix_t q, element_t el)
{
  q->arr[QINC(end)] = el;
}

element_t queue_fix_dequeue(queue_fix_t q)
{
  return q->arr[QINC(front)];
}

element_t queue_fix_front(queue_fix_t q)
{
  return q->arr[q->front];
}

bool queue_fix_is_full(queue_fix_t q)
{
  return (queue_fix_size_phy(q) - queue_fix_size(q)) <= 1;
}

bool queue_fix_is_empty(queue_fix_t q)
{
  return q->front == q->end;
}

size_t queue_fix_size(queue_fix_t q)
{
  return (q->end - q->front) + ((q->end >= q->front) ?  0 : q->size);
}

size_t queue_fix_size_phy(queue_fix_t q)
{
  return q->size;
}
