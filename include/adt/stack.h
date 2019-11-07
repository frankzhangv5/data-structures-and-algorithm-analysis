#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

#include "type.h"

typedef struct _stack_entity {
    int capacity;
    int size;
    int top;
    element_t *arr;
} stack_entity_t;

typedef stack_entity_t *_stack_t;

_stack_t create_stack(int capacity);
void dispose_stack(_stack_t stack);
void make_stack_empty(_stack_t stack);
bool is_stack_empty(_stack_t stack);
bool is_stack_full(_stack_t stack);
bool push(_stack_t stack, element_t e);
element_t pop(_stack_t stack);
element_t top(_stack_t stack);

#endif