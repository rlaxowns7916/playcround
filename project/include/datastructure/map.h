#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct MapEntry{
    unsigned int hash; 
    unsigned short keyLen;
    struct MapEntry* next;
    void* value;
    unsigned char key[]; 
}MapEntry;

typedef struct MapBucket{
    unsigned short size;
    MapEntry* head;
} MapBucket;

typedef struct Map {
    unsigned int size;
    MapBucket* buckets;
} Map;



Map*     map_create();
void     map_destroy(Map* map);
bool     map_put(Map* map, const void* key, size_t keyLen, void* value);
void*    map_get(const Map* map, const void* key, size_t keyLen);
bool     map_remove(Map* map, const void* key, size_t keyLen);

#endif