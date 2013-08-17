#ifndef _OBJSPACE_H
#define _OBJSPACE_H

#include <unistd.h>

#include "object.h"

typedef struct _string String;

typedef struct {
    Object object;

} Map;

typedef struct {
    Object object;
    Object **array;
    int length;
} List;

typedef struct {
    Object object;
    union {
        int num_int;
        double num_float;
    } value;

} Number;

struct _string {
    Object object;
    char *ptr;
};

#define NUMBER_TYPE  0x10
#define NUMBER_INT   0x11
#define NUMBER_FLOAT 0x12

#define MAP_TYPE     0x20
#define MAP_HASH     0x21
#define MAP_BTREE    0x22

#define LIST_TYPE    0x40
#define LIST_ARRAY   0x41
#define LIST_TUPLE   0x42
#define LIST_LINKED  0x43
#define LIST_QUEUE   0x44

#define STRING_TYPE  0x81

Object *list_array_create();


#endif
