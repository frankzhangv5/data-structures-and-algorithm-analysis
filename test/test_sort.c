#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include <sort/sort.h>
#include <sort/util.h>

#ifdef SUITE_NAME
#undef SUITE_NAE
#endif

#define SUITE_NAME "sort_testsuite"

#define NELEM 500

static void test_sort() {

    clock_t start;
    element_t *unsorted = NULL;

    int size = NELEM * sizeof(element_t);
    unsorted = (element_t *)malloc(size);
    if (!unsorted)
        return;

    fill_array(unsorted, NELEM, 1000);
    start = clock();
    insertion_sort(unsorted, NELEM);
    SPENT_SEC("insertion_sort", start);
    print_array(unsorted, NELEM, "insertion_sort");

    fill_array(unsorted, NELEM, 1000);
    start = clock();
    shell_sort(unsorted, NELEM);
    SPENT_SEC("shell_sort", start);
    print_array(unsorted, NELEM, "shell_sort");

    fill_array(unsorted, NELEM, 1000);
    start = clock();
    merge_sort(unsorted, NELEM);
    SPENT_SEC("merge_sort", start);
    print_array(unsorted, NELEM, "merge_sort");

    fill_array(unsorted, NELEM, 1000);
    start = clock();
    heap_sort(unsorted, NELEM);
    SPENT_SEC("heap_sort", start);
    print_array(unsorted, NELEM, "heap_sort");

    fill_array(unsorted, NELEM, 1000);
    start = clock();
    quick_sort(unsorted, NELEM);
    SPENT_SEC("quick_sort", start);
    print_array(unsorted, NELEM, "quick_sort");

    free(unsorted);
}

static CU_TestInfo testcases[] = {{"test_sort", test_sort}, CU_TEST_INFO_NULL};

static int suite_init() { return 0; }

static int suite_cleanup() { return 0; }

static void case_setup() {}

static void case_teardown() {}

const CU_SuiteInfo sort_testsuite = {SUITE_NAME, suite_init,    suite_cleanup,
                                     case_setup, case_teardown, testcases};