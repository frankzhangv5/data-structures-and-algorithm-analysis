#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <adt/queue.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "queue_testsuite"

static queue_t queue = NULL;

static void test_is_queue_empty() { CU_ASSERT_TRUE(is_queue_empty(queue)); }

static void test_enqueue() {
    CU_ASSERT_EQUAL(-1, front(queue));
    CU_ASSERT_EQUAL(-1, dequeue(queue));
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    CU_ASSERT_TRUE(enqueue(queue, 4));
    enqueue(queue, 5);
    CU_ASSERT_FALSE(enqueue(queue, 6));
    enqueue(queue, 7);
    enqueue(queue, 8);
    enqueue(queue, 9);
    CU_ASSERT_FALSE(is_queue_empty(queue));

    CU_ASSERT_EQUAL(1, front(queue));
}

static void test_dequeue() {
    element_t e = dequeue(queue);
    CU_ASSERT_EQUAL(1, e);
    CU_ASSERT_EQUAL(2, front(queue));
}

static CU_TestInfo testcases[] = {{"test_is_queue_empty", test_is_queue_empty},
                                  {"test_enqueue", test_enqueue},
                                  {"test_dequeue", test_dequeue},
                                  CU_TEST_INFO_NULL};

static int suite_init() {
    queue = create_queue(5);
    return 0;
}

static int suite_cleanup() {
    dispose_queue(queue);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo queue_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                      case_setup, case_teardown, testcases};