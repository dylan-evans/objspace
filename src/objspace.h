#include <unistd.h>

typedef struct _object Object;
typedef struct _key Key;
typedef struct _iter Iter;
typedef struct _lock Lock;

typedef struct {
    int (*set)(Object *, Key *, Object *);
    Object *(*get)(Object *, Key *);
    int (*destroy)(Object *, Key *);
    Iter *(*iter)(Object *);
    Object *(*next)(Iter *);
    Lock *(*lock)(Object *, int);
    int (*length)(Object *);
    char *(*string)(Object *);
} Engine;

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
};

struct _key {
    char *str;
    unsigned int index;
};

typedef struct {
    Object object;

} Map;

typedef struct {
    Object object;

} List;

typedef struct {
    Object object;
    union {
        int num_int;
        double num_float;
    } value;

} Number;


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

