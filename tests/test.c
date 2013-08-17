#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>

#include "objspace.h"

#define FALSE 0
#define TRUE 1

int main(int argc, char **argv)
{
    int status;

    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    if(!(status = setup_object_tests())
        || !(status = setup_list_tests()))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    CU_automated_run_tests();
    CU_list_tests_to_file();

    //CU_console_run_tests();


    CU_cleanup_registry();

    return CU_get_error();
}

