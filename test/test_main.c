#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern const CU_SuiteInfo list_testsuite;
extern const CU_SuiteInfo stack_testsuite;
extern const CU_SuiteInfo queue_testsuite;
extern const CU_SuiteInfo bst_testsuite;
extern const CU_SuiteInfo avltree_testsuite;
extern const CU_SuiteInfo priority_queue_testsuite;
extern const CU_SuiteInfo sort_testsuite;

int main(int argc, char **argv) {
    if (CU_initialize_registry()) {
        fprintf(stderr, "Initialization of Test Registry failed.\n");
        return EXIT_FAILURE;
    } else {
        assert(NULL != CU_get_registry());
        assert(!CU_is_test_running());

        CU_SuiteInfo suites[] = {list_testsuite,           stack_testsuite,
                                 queue_testsuite,          bst_testsuite,
                                 priority_queue_testsuite, avltree_testsuite,
                                 sort_testsuite,           CU_SUITE_INFO_NULL};

        if (CUE_SUCCESS != CU_register_suites(suites)) {
            return EXIT_FAILURE;
        }

        /**** Automated Mode *****************/
        // CU_set_output_filename("TestMax");
        // CU_list_tests_to_file();
        // CU_automated_run_tests();
        /************************************/

        /***** Basice Mode *******************/
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        /************************************/

        /*****Console Mode ********************/
        // CU_console_run_tests();
        /************************************/

        CU_cleanup_registry();

        return CU_get_error();
    }
}