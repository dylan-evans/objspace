#ifndef _OBJECT_H
#define _OBJECT_H

#include <unistd.h>

typedef struct _object Object;
typedef struct _engine Engine;
typedef struct _key Key;
typedef struct _iter Iter;
typedef struct _lock Lock;
typedef struct _string String;

struct _engine {
    int     (*set)(Object *, Key *, Object *);
    Object *(*get)(Object *, Key *);
    int     (*destroy)(Object *, Key *);
    Iter   *(*iter)(Object *);
    Object *(*next)(Iter *);
    Lock   *(*lock)(Object *, int);
    int     (*unlock)(Lock *);
    int     (*length)(Object *);
    char   *(*string)(Object *);
};

/*
 * The Object is a base for any data.
 */
struct _object {
    int type, size;
    Object *container;
    Engine *engine;
};

struct _iter {
    Object *object;
    int index;
};

struct _lock {
    int id;
    Object *object;
};

struct _key {
    char *str;
    unsigned int index;
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

Object *object_float(double value);
Object *object_int(int value);
Object *object_string(char *buffer);
Key *key_index(int index);

#endif
