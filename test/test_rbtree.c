#include <CUnit/CUnit.h>
#include <adt/rbtree.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "rbtree_testsuite"

static rbtree_t *tree;

static void test_rbtree_insert() {
    int nodes[] = {63, 47, 58, 88, 37, 32, 29, 99, 43, 42,
                   71, 89, 32, 29, 99, 33, 44, 55, 66, 45};
    int i;
    for (i = 0; i < sizeof(nodes) / sizeof(nodes[0]); i++) {
        tree = rbtree_insert(tree, nodes[i]);
    }

    CU_ASSERT_PTR_NOT_NULL(tree);
}

static void test_rbtree_delete() {
    rbtree_node_t *min = rbtree_find_min(tree);
    CU_ASSERT_PTR_NOT_NULL(min);
    element_t min_key = min->element;

    tree = rbtree_delete(tree, min->element);
    CU_ASSERT_PTR_NOT_NULL(tree);

    rbtree_node_t *min2 = rbtree_find_min(tree);
    CU_ASSERT_NOT_EQUAL(min_key, min2->element);
}

static CU_TestInfo testcases[] = {{"test_rbtree_insert", test_rbtree_insert},
                                  {"test_rbtree_delete", test_rbtree_delete},
                                  CU_TEST_INFO_NULL};

static int suite_init() {
    tree = rbtree_init();
    return 0;
}

static int suite_cleanup() {
    dispose_rbtree(tree);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo rbtree_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                       case_setup, case_teardown, testcases};