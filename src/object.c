#include <malloc.h>
#include "objspace.h"



char *number_string(Object *obj);

/* 
 * Generic object functions which can be used on any object.
 */

int obj_set(Object *self, Key *key, Object *obj)
{
    if(self->engine->set == NULL)
        return 0;
    return self->engine->set(self, key, obj);
}

Object *obj_get(Object *self, Key *key)
{
    if(self->engine->get == NULL)
        return NULL;
    return self->engine->get(self, key);
}

int obj_destroy(Object *self, Key *key)
{
    if(self->engine->destroy == NULL)
        return 0;
    return self->engine->destroy(self, key);
}

Iter *obj_iter(Object *self)
{
    if(self->engine->iter == NULL)
        return NULL;
    return self->engine->iter(self);
}

Object *obj_next(Iter *iter)
{
    if(iter->object->engine->next == NULL)
        return NULL;
    return iter->object->engine->next(iter);
}

/**
 * Lock the object. If the object is a container then the lock cannot be
 * acquired while any child object is locked. 
 * @param timeout Sets the maximum time to wait, 0 forever, -1 don't wait
 */
Lock *obj_lock(Object *self, int timeout)
{
    if(self->engine->lock == NULL)
        return NULL;
    return self->engine->lock(self, timeout);
}

/**
 * Release the object.
 * @param lock The lock which must be freed by the unlock function.
 */
int obj_unlock(Lock *lock)
{
    if(lock->object->engine->unlock == NULL)
        return 0;
    return lock->object->engine->unlock(lock);
}

/**
 * The length of the object. This is distinct from the storage size of the 
 * object itself and should indicate either the number of items in a container
 * or the maximum bounds of the container depending on what is practical for
 * a given container.
 * @param self The object to get the value from.
 */
int obj_length(Object *self)
{
    if(self->engine->length == NULL)
        return -1;
    return self->engine->length(self);
}

/**
 * Render the object as a string. 
 * @param self The object to render.
 */
char *obj_string(Object *self)
{
    if(self->engine->string == NULL)
        return NULL;
    return self->engine->string(self);
}


Lock *object_lock(Object *object, int timeout)
{
    Lock *lock;
}

Key *key_from_int(Object *object, int index)
{
       
}

Key *key_index(int index)
{
    Key *key;

    key = malloc(sizeof(Key));
    key->index = index;
    return key;
}

/* Either int or float */
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

Object *object_string(char *buffer)
{
    static Engine str_engine = {
        .set = NULL,
        .get = NULL,
        .destroy = NULL,
        .iter = NULL,
        .next = NULL,
        .lock = NULL,
        .length = NULL,
        .string = NULL
    };
    String *str;

    str = malloc(sizeof(String));

    str->object.type = STRING_TYPE;
    str->object.size = sizeof(String);
    str->object.engine = &str_engine;
    str->object.container = NULL;
    str->ptr = buffer;

    return (Object*)str;
}


