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

int init_suite_list()
{
    return 0;
}

int clean_suite_list()
{
    return 0;
}

void test_list1()
{
    int i, prev;
    List *list;
    Object *val;
    Key *key;

    list = (List*) list_array_create();

    CU_ASSERT(list != NULL);

    val = object_int(42);
    
    for(i = 1, prev = 1; i < 1000000; i += prev)
    {
        key = key_index(i);
        obj_set((Object*)list, key, val);
        CU_ASSERT(list->length > i);
    }

}


int setup_list_tests()
{
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("List Suite", init_suite_list, 
                          clean_suite_list);
    
    if(pSuite == NULL
        || !CU_add_test(pSuite, "List test 1", test_list1))
    {
        return 0;
    }

    return 1;
}

