#include <adt/queue.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

queue_t create_queue(int capacity) {
    assert(capacity > 0);

    queue_t queue = (queue_entity_t *)malloc(sizeof(queue_entity_t));
    if (!queue) {
        perror("create_queue");
        return NULL;
    }
    memset(queue, 0, sizeof(queue_entity_t));

    queue->arr = (element_t *)malloc(sizeof(element_t) * capacity);
    if (!queue->arr) {
        perror("create_queue2");
        free(queue);
        queue = NULL;
        return NULL;
    }
    queue->capacity = capacity;
    make_queue_empty(queue);

    return queue;
}
void dispose_queue(queue_t queue) {
    assert(NULL != queue);

    make_queue_empty(queue);

    free(queue->arr);
    free(queue);
    queue = NULL;
}

void make_queue_empty(queue_t queue) {
    assert(NULL != queue);

    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    memset(queue->arr, 0, sizeof(element_t) * (queue->capacity));
}

bool is_queue_empty(queue_t queue) { return !queue || !queue->size; }

bool is_queue_full(queue_t queue) {
    assert(NULL != queue);

    if (queue->size == queue->capacity)
        return true;

    return false;
}

bool enqueue(queue_t queue, element_t e) {
    assert(NULL != queue);

    if (!is_queue_full(queue)) {
        queue->rear++;
        if (queue->rear == queue->capacity)
            queue->rear = 0;

        queue->arr[queue->rear] = e;
        queue->size++;
        return true;
    }

    return false;
}

element_t dequeue(queue_t queue) {
    assert(NULL != queue);

    if (!is_queue_empty(queue)) {
        element_t e = front(queue);
        queue->front++;
        if (queue->front == queue->capacity)
            queue->front = 0;

        queue->size--;
        return e;
    }

    return -1;
}

element_t front(queue_t queue) {
    assert(NULL != queue);

    if (!is_queue_empty(queue))
        return queue->arr[queue->front];

    return -1;
}