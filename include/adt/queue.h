#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "type.h"
#include <stdbool.h>

typedef struct _queue_entity {
    int capacity;
    int size;
    int front;
    int rear;
    element_t *arr;
} queue_entity_t;

typedef queue_entity_t *queue_t;

queue_t create_queue(int capacity);
void dispose_queue(queue_t queue);
void make_queue_empty(queue_t queue);
bool is_queue_empty(queue_t queue);
bool is_queue_full(queue_t queue);
bool enqueue(queue_t queue, element_t e);
element_t dequeue(queue_t queue);
element_t front(queue_t queue);

#endif