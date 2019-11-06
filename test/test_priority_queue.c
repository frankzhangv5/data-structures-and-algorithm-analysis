#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <adt/priority_queue.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "priority_queue_testsuite"

static priority_queue_t queue = NULL;

static void test_is_priority_queue_empty() {
    CU_ASSERT_TRUE(is_priority_queue_empty(queue));
}

static void test_insert_into_priority_queue() {
    CU_ASSERT_EQUAL(-32767, delete_min_of_priority_queue(queue));
    insert_into_priority_queue(queue, 1);
    insert_into_priority_queue(queue, 2);
    insert_into_priority_queue(queue, 3);
    insert_into_priority_queue(queue, 5);
    insert_into_priority_queue(queue, 6);
    insert_into_priority_queue(queue, 7);
    insert_into_priority_queue(queue, 8);
    insert_into_priority_queue(queue, 9);
    CU_ASSERT_FALSE(is_priority_queue_empty(queue));
}

static void test_delete_min_of_priority_queue() {
    element_t e = delete_min_of_priority_queue(queue);
    CU_ASSERT_EQUAL(1, e);
    e = delete_min_of_priority_queue(queue);
    CU_ASSERT_EQUAL(2, e);
}

static CU_TestInfo testcases[] = {
    {"test_is_priority_queue_empty", test_is_priority_queue_empty},
    {"test_insert_into_priority_queue", test_insert_into_priority_queue},
    {"test_delete_min_of_priority_queue", test_delete_min_of_priority_queue},
    CU_TEST_INFO_NULL};

static int suite_init() {
    queue = create_priority_queue(8);
    return 0;
}

static int suite_cleanup() {
    dispose_priority_queue(queue);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo priority_queue_testsuite = {SUITE_NAME,    suite_init,
                                               suite_cleanup, case_setup,
                                               case_teardown, testcases};