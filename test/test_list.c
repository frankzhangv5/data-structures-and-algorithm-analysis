#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <adt/list.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "list_testsuite"

static list_t list = NULL;

static void test_is_list_empty() { CU_ASSERT_TRUE(is_list_empty(list)); }

static void test_insert() {
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    insert(list, 5);
    insert(list, 6);
    insert(list, 7);
    insert(list, 5);

    CU_ASSERT_FALSE(is_list_empty(list));

    CU_ASSERT_EQUAL(5, retrieve(first(list)));
}

static void test_find() {
    position_t p = find(list, 4);
    CU_ASSERT_PTR_NOT_NULL(p);
    CU_ASSERT_EQUAL(4, retrieve(p));
    p = find(list, 11);
    CU_ASSERT_PTR_NULL(p);
}

static void test_find_prev() {
    position_t p = find_prev(list, 4);
    CU_ASSERT_PTR_NOT_NULL(p);
    CU_ASSERT_EQUAL(5, retrieve(p));
    p = find_prev(list, 11);
    CU_ASSERT_PTR_NULL(p);
}

static void test_drop() {
    drop(list, 5);
    position_t p = find(list, 5);
    CU_ASSERT_PTR_NULL(p);
}

static void test_first() {
    CU_ASSERT_EQUAL(7, retrieve(first(list)));
    drop(list, 7);
    CU_ASSERT_EQUAL(6, retrieve(first(list)));
}

static CU_TestInfo testcases[] = {{"test_is_list_empty", test_is_list_empty},
                                  {"test_insert", test_insert},
                                  {"test_find", test_find},
                                  {"test_find_prev", test_find_prev},
                                  {"test_drop", test_drop},
                                  {"test_first", test_first},
                                  CU_TEST_INFO_NULL};

static int suite_init() {
    list = create_list();
    return 0;
}

static int suite_cleanup() {
    dispose_list(list);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo list_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                     case_setup, case_teardown, testcases};