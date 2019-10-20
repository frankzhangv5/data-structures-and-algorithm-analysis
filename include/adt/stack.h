#ifndef _STACK_H_
#define _STACK_H_

#include "type.h"
#include <stdbool.h>

typedef struct _stack_entity {
    int capacity;
    int size;
    int top;
    element_t *arr;
} stack_entity_t;

typedef stack_entity_t *stack_t;

stack_t create_stack(int capacity);
void dispose_stack(stack_t stack);
void make_stack_empty(stack_t stack);
bool is_stack_empty(stack_t stack);
bool is_stack_full(stack_t stack);
bool push(stack_t stack, element_t e);
element_t pop(stack_t stack);
element_t top(stack_t stack);

#endif