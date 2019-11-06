#include <adt/priority_queue.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

priority_queue_t create_priority_queue(int capacity) {
    assert(capacity > 0);

    priority_queue_t queue = (priority_queue_t)malloc(sizeof(heap_entity_t));
    if (!queue) {
        perror("create_priority_queue");
        return NULL;
    }
    memset(queue, 0, sizeof(heap_entity_t));

    queue->arr = (element_t *)malloc(sizeof(element_t) * capacity);
    if (!queue->arr) {
        perror("create_priority_queue2");
        free(queue);
        queue = NULL;
        return NULL;
    }
    queue->capacity = capacity;
    make_priority_queue_empty(queue);

    return queue;
}
void dispose_priority_queue(priority_queue_t queue) {

    assert(NULL != queue);

    make_priority_queue_empty(queue);

    free(queue->arr);
    // free(queue);
    queue = NULL;
}
void make_priority_queue_empty(priority_queue_t queue) {
    assert(NULL != queue);

    queue->size = 0;
    memset(queue->arr, 0, sizeof(element_t) * (queue->capacity));
    queue->arr[0] = -32767;
}
bool is_priority_queue_empty(priority_queue_t queue) {
    return !queue || !queue->size;
}
bool is_priority_queue_full(priority_queue_t queue) {
    assert(NULL != queue);

    if (queue->size == queue->capacity)
        return true;

    return false;
}
void insert_into_priority_queue(priority_queue_t queue, element_t e) {
    assert(NULL != queue);

    if (!is_priority_queue_full(queue)) {
        int i;
        for (i = ++queue->size; queue->arr[i / 2] > e; i /= 2) // percolate up
            queue->arr[i] = queue->arr[i / 2];
        queue->arr[i] = e;
    }
}

element_t delete_min_of_priority_queue(priority_queue_t queue) {
    assert(NULL != queue);

    int i, child;
    element_t min_elem, last_elem;

    if (is_priority_queue_empty(queue)) {
        return queue->arr[0];
    }

    min_elem = queue->arr[1];
    last_elem = queue->arr[queue->size];
    queue->size--;

    for (i = 1; i * 2 <= queue->size; i = child) {
        child = i * 2;
        // find smaller child
        if (child != queue->size && queue->arr[child + 1] < queue->arr[child]) {
            child++;
        }

        // percolate one level
        if (last_elem > queue->arr[child]) {
            queue->arr[i] = queue->arr[child];
        } else {
            break;
        }
    }
    queue->arr[i] = last_elem;
    return min_elem;
}
element_t find_min_of_priority_queue(priority_queue_t queue) {
    assert(NULL != queue);

    if (!is_priority_queue_empty(queue)) {
        return queue->arr[1];
    }

    return queue->arr[0];
}