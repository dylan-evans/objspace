#include <malloc.h>

#include "objspace.h"

int map_hash_set(Object *self, Key *key, Object *value);
Object *map_hash_get(Object *self, Key *key);
int map_hash_destroy(Object *self, Key *key);
Iter *map_hash_iter(Object *self);
Object *map_hash_next(Iter *iter);
Lock *map_hash_lock(Object *self, int timeout);

Object *map_create_with_engine(Engine *engine, int type)
{
    Map *map;

    map = malloc(sizeof(Map));
    if(!map) return NULL;

    map->object.type = type;
    map->object.size = sizeof(Map);
    map->object.engine = engine;
    map->object.container = NULL;

    return (Object *)map;
}

Object *map_hash_create()
{
    static Engine map_engine = {
        .set = map_hash_set,
        .get = map_hash_get,
        .destroy = map_hash_destroy,
        .iter = map_hash_iter,
        .next = map_hash_next,
        .lock = map_hash_lock
    };
    
    return map_create_with_engine(&map_engine, MAP_HASH);
}

int map_hash_set(Object *self, Key *key, Object *value)
{
    
}

Object *map_hash_get(Object *self, Key *key)
{

}

int map_hash_destroy(Object *self, Key *key)
{

}

Iter *map_hash_iter(Object *self)
{

}

Object *map_hash_next(Iter *iter)
{

}

Lock *map_hash_lock(Object *self, int timeout)
{

}

