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

int init_suite_object()
{
    return 0;
}

int clean_suite_object()
{
    return 0;
}

void test_object1()
{
    CU_ASSERT(TRUE);
}


int init_suite_num()
{
    return 0;
}

int clean_suite_num()
{
    return 0;
}

void test_num1()
{
    CU_ASSERT(TRUE);
}

int setup_object_tests()
{
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("Object Suite", init_suite_object, 
                          clean_suite_object);
    
    if(pSuite == NULL
        || !CU_add_test(pSuite, "Object test 1", test_object1))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Number Suite", init_suite_num, clean_suite_num);

    if(!pSuite
        || !CU_add_test(pSuite, "Number test 1", test_num1))
    {
        return 0;
    }
    return 1;
}
