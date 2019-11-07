#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <stdbool.h>

#include "type.h"

typedef struct _heap_entity {
    int capacity;
    int size;
    element_t *arr;
} heap_entity_t;

typedef heap_entity_t *heap_t;

typedef heap_t priority_queue_t;

priority_queue_t create_priority_queue(int capacity);
void dispose_priority_queue(priority_queue_t pq);
void make_priority_queue_empty(priority_queue_t pq);
bool is_priority_queue_empty(priority_queue_t pq);
bool is_priority_queue_full(priority_queue_t pq);
void insert_into_priority_queue(priority_queue_t pq, element_t e);
element_t delete_min_of_priority_queue(priority_queue_t pq);
element_t find_min_of_priority_queue(priority_queue_t pq);

#endif