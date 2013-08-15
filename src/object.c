#include <malloc.h>
#include "objspace.h"



char *number_string(Object *obj);

/**
 * \param timeout Sets the maximum time to wait, 0 forever, -1 don't wait
 */
Lock *object_lock(Object *object, int timeout)
{
    Lock *lock;
}

Key *key_from_int(Object *object, int index)
{
    
}

Number *number_create(int type)
{
    /* Number doesn't do anything */
    static Engine num_engine = {
        .set = NULL,
        .get = NULL,
        .destroy = NULL,
        .iter = NULL,
        .next = NULL,
        .lock = NULL,
        .length = NULL,
        .string = number_string
    };
    Number *num;

    num = malloc(sizeof(Number));
    num->object.type = type;
    num->object.size = sizeof(Number);
    num->object.engine = &num_engine;
    num->object.container = NULL;

    return num;
}

char *number_string(Object *obj)
{
    char *buf;

    /* TODO: Make better */
    buf = malloc(64);

    switch(obj->type)
    {
        case NUMBER_INT:
            sprintf(buf, "%d", ((Number *)(obj))->value.num_int);
            break;
        case NUMBER_FLOAT:
            sprintf(buf, "%f", ((Number *)(obj))->value.num_float);
            break;
        default:
            free(buf);
            return NULL;
    }
    return buf;
}

Object *object_float(double value)
{
    Number *num;

    num = number_create(NUMBER_FLOAT);
    num->value.num_float = value;

    return (Object*)num;
}

Object *object_int(int value)
{
    Number *num;

    num = number_create(NUMBER_INT);
    num->value.num_int = value;

    return (Object*)num;
}

