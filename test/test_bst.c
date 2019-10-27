#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <adt/bst.h>
#include <ui/ui.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "bst_testsuite"

static tree_node_t *tree;

static void test_insert_into_tree() {
    int nodes[] = {63, 47, 58, 88, 37, 32, 29, 99, 43, 42,
                   71, 89, 32, 29, 99, 33, 44, 55, 66, 45};
    int i;
    for (i = 0; i < sizeof(nodes) / sizeof(nodes[0]); i++) {
        tree = insert_into_tree(tree, nodes[i]);
    }

    CU_ASSERT_PTR_NOT_NULL(tree);

    CU_ASSERT_EQUAL(63, get_value(tree));
}

static void test_find_tree_node() {
    tree_node_t *p = find_tree_node(tree, 71);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(71, get_value(p));

    p = find_tree_node(tree, 100);
    CU_ASSERT_PTR_NULL(p);
}

static void test_find_min() {
    tree_node_t *p = find_min(tree);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(28, get_value(p));
}

static void test_find_max() {
    tree_node_t *p = find_max(tree);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(99, get_value(p));
}

static void test_delete_tree_node() {
    tree_node_t *p = find_tree_node(tree, 71);
    CU_ASSERT_PTR_NOT_NULL(p);

    CU_ASSERT_EQUAL(71, get_value(p));
    tree = delete_tree_node(tree, 71);
    p = find_tree_node(tree, 71);
    CU_ASSERT_PTR_NULL(p);
}

static void visit(tree_node_t *node) {
    if (node) {
        printf("%d ", node->element);
    }
}

static void level_visit(tree_node_t *node, int level) {
    if (node) {
        printf("%d(%d) ", node->element, level);
    }
}

static void test_traverse() {
    printf("\npreorder_traverse:");
    preorder_traverse(tree, visit);
    printf("\ninorder_traverse:");
    inorder_traverse(tree, visit);
    printf("\npostorder_traverse:");
    postorder_traverse(tree, visit);
    printf("\nlevelorder_traverse:");
    levelorder_traverse(tree, level_visit);
    printf("\n");
    draw_tree(tree);
}

static CU_TestInfo testcases[] = {
    {"test_insert_into_tree", test_insert_into_tree},
    {"test_find_tree_node", test_find_tree_node},
    {"test_find_min", test_find_min},
    {"test_find_max", test_find_max},
    {"test_traverse", test_traverse},
    {"test_delete_tree_node", test_delete_tree_node},
    CU_TEST_INFO_NULL};

static int suite_init() { return 0; }

static int suite_cleanup() {
    destroy_tree(tree);
    return 0;
}

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo bst_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                    case_setup, case_teardown, testcases};