#include <adt/stack.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_stack_t create_stack(int capacity) {
    assert(capacity > 0);

    _stack_t stack = (stack_entity_t *)malloc(sizeof(stack_entity_t));
    if (!stack) {
        perror("create_stack");
        return NULL;
    }
    memset(stack, 0, sizeof(stack_entity_t));

    stack->capacity = capacity;
    stack->top = -1;

    stack->arr = (element_t *)malloc(sizeof(element_t) * capacity);
    if (!stack->arr) {
        perror("create_stack2");
        free(stack);
        stack = NULL;
        return NULL;
    }
    memset(stack->arr, 0, sizeof(element_t) * capacity);

    return stack;
}

void dispose_stack(_stack_t stack) {
    assert(NULL != stack);

    make_stack_empty(stack);

    free(stack->arr);
    free(stack);
    stack = NULL;
}

void make_stack_empty(_stack_t stack) {
    assert(NULL != stack);

    stack->size = 0;
    stack->top = -1;
    memset(stack->arr, 0, sizeof(element_t) * (stack->capacity));
}

bool is_stack_empty(_stack_t stack) { return !stack || !stack->size; }

bool is_stack_full(_stack_t stack) {
    assert(NULL != stack);

    if (stack->size == stack->capacity)
        return true;

    return false;
}

bool push(_stack_t stack, element_t e) {
    assert(NULL != stack);

    if (!is_stack_full(stack)) {
        stack->top++;
        stack->arr[stack->top] = e;
        stack->size++;
        return true;
    }

    return false;
}

element_t pop(_stack_t stack) {
    assert(NULL != stack);

    if (!is_stack_empty(stack)) {
        element_t e = top(stack);
        stack->top--;
        stack->size--;
        return e;
    }

    return -1;
}

element_t top(_stack_t stack) {
    assert(NULL != stack);

    if (!is_stack_empty(stack)) {
        return stack->arr[stack->top];
    }

    return -1;
}