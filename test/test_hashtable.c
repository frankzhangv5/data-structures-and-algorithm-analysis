#include <CUnit/CUnit.h>
#include <adt/hashtable.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "hashtable_testsuite"

static hashtable_t *table = NULL;

static void test_is_hashtable_empty() {
    CU_ASSERT_TRUE(is_hashtable_empty(table));
}

static void test_hashtable_set() {
    hashtable_set(table, "name", "frank");
    hashtable_set(table, "family", "zhang");
    hashtable_set(table, "son", "yixuan");

    CU_ASSERT_FALSE(is_hashtable_empty(table));
    CU_ASSERT_FALSE(is_hashtable_full(table));
}

static void test_hashtable_get() {
    const char *name = hashtable_get(table, "name");
    CU_ASSERT_PTR_NOT_NULL(name);
    CU_ASSERT_STRING_EQUAL(name, "frank");

    const char *p = hashtable_get(table, "foo");
    CU_ASSERT_PTR_NULL(p);
}

static void test_hashtable_remove() {
    hashtable_remove(table, "name");
    hashtable_remove(table, "bar");

    const char *name = hashtable_get(table, "name");
    CU_ASSERT_PTR_NULL(name);
}

static CU_TestInfo testcases[] = {
    {"test_is_hashtable_empty", test_is_hashtable_empty},
    {"test_hashtable_set", test_hashtable_set},
    {"test_hashtable_get", test_hashtable_get},
    {"test_hashtable_remove", test_hashtable_remove},
    CU_TEST_INFO_NULL};

static int suite_init() {
    table = create_hashtable(20);
    return 0;
}

static int suite_cleanup() {
    dispose_hashtable(table);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo hashtable_testsuite = {SUITE_NAME,    suite_init,
                                          suite_cleanup, case_setup,
                                          case_teardown, testcases};