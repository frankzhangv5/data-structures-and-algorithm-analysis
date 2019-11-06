#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <adt/avltree.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "avltree_testsuite"

static avltree_t tree;

static void test_insert_into_avltree() {
    int nodes[] = {63, 47, 58, 88, 37, 32, 29, 99, 43, 42,
                   71, 89, 32, 29, 99, 33, 44, 55, 66, 45};
    int i;
    for (i = 0; i < sizeof(nodes) / sizeof(nodes[0]); i++) {
        tree = insert_into_avltree(tree, nodes[i]);
    }

    CU_ASSERT_PTR_NOT_NULL(tree);

    CU_ASSERT_EQUAL(58, tree->element);
}

static void test_find_avltree_node() {
    avltree_node_t *p = find_avltree_node(tree, 71);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(71, p->element);

    p = find_avltree_node(tree, 100);
    CU_ASSERT_PTR_NULL(p);
}

static void test_find_avltree_min() {
    avltree_node_t *p = find_avltree_min(tree);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(29, p->element);
}

static void test_find_avltree_max() {
    avltree_node_t *p = find_avltree_max(tree);
    CU_ASSERT_PTR_NOT_NULL(p);
    CU_ASSERT_EQUAL(99, p->element);
}

static CU_TestInfo testcases[] = {
    {"test_insert_into_avltree", test_insert_into_avltree},
    {"test_find_avltree_node", test_find_avltree_node},
    {"test_find_avltree_min", test_find_avltree_min},
    {"test_find_avltree_max", test_find_avltree_max},
    CU_TEST_INFO_NULL};

static int suite_init() { return 0; }

static int suite_cleanup() {
    destroy_avltree(tree);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo avltree_testsuite = {SUITE_NAME,    suite_init,
                                        suite_cleanup, case_setup,
                                        case_teardown, testcases};