#ifndef _TYPE_H_
#define _TYPE_H_

typedef int element_t;

typedef struct _singly_linked_node {
    element_t element;
    struct _singly_linked_node *next;
} singly_linked_node_t;

typedef struct _doubly_linked_node {
    element_t element;
    struct _doubly_linked_node *prev;
    struct _doubly_linked_node *next;
} doubly_linked_node_t;

typedef struct _point {
    int y;
    int x;
} point_t;

#endif