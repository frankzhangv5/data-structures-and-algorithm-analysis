#include <CUnit/CUnit.h>
#include <adt/stack.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "stack_testsuite"

static _stack_t stack = NULL;

static void test_is_stack_empty() { CU_ASSERT_TRUE(is_stack_empty(stack)); }

static void test_push() {
    CU_ASSERT_EQUAL(-1, pop(stack));
    CU_ASSERT_EQUAL(-1, top(stack));
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    CU_ASSERT_TRUE(push(stack, 4));
    push(stack, 5);
    CU_ASSERT_FALSE(push(stack, 6));
    push(stack, 7);
    push(stack, 8);
    push(stack, 9);
    CU_ASSERT_FALSE(is_stack_empty(stack));

    CU_ASSERT_EQUAL(5, top(stack));
}

static void test_pop() {
    element_t e = pop(stack);
    CU_ASSERT_EQUAL(5, e);
    CU_ASSERT_EQUAL(4, top(stack));
}

static CU_TestInfo testcases[] = {{"test_is_stack_empty", test_is_stack_empty},
                                  {"test_push", test_push},
                                  {"test_pop", test_pop},
                                  CU_TEST_INFO_NULL};

static int suite_init() {
    stack = create_stack(5);
    return 0;
}

static int suite_cleanup() {
    dispose_stack(stack);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo stack_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                      case_setup, case_teardown, testcases};