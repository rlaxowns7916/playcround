#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "datastructure/map.h"


const int BUCKET_SIZE = 64;

unsigned int hash(char key[], unsigned short len){
    unsigned int h = 0;
    const unsigned int seed = 131;
    for (int i = 0; i < len; i++) {
        h = h * seed + key[i];
    }
    return h;
}


Map* map_create(){
    Map* map = calloc(1, sizeof(Map));
    if (!map) return NULL;
    
    map->buckets = calloc(BUCKET_SIZE, sizeof(MapBucket));
    if (!map->buckets) {
        free(map);
        return NULL;
    }

    return map;
}

void*  map_get(const Map* map, const void* key, size_t keyLen){
    unsigned int hashKey = hash((unsigned char*)key, keyLen);
    unsigned short bucketKey = hashKey % BUCKET_SIZE;
    
    MapBucket* bucket = &map->buckets[bucketKey];
    
    if(bucket->size == 0){
        return NULL;
    }

    MapEntry* cursor = bucket->head;
    while(cursor != NULL){
        if(cursor->hash == hashKey 
            &&  memcmp((unsigned char*)key, cursor->key, keyLen) == 0){
            return cursor->value;
        }
        cursor = cursor->next;
    }

    return NULL;
}

bool map_put(Map* map, const void* key, size_t keyLen, void* value){
    unsigned int hashKey = hash((unsigned char*) key, keyLen);
    unsigned short bucketKey = hashKey % BUCKET_SIZE;

    MapBucket* bucket = &map->buckets[bucketKey];
    MapEntry* cursor = bucket->head;

    while(cursor != NULL){
         if(cursor->hash == hashKey 
            &&  memcmp((unsigned char*)key, cursor->key, keyLen) == 0){
            cursor->value = value;
            
            return true;
        }
        cursor = cursor->next;
    }

    MapEntry* entry = malloc(sizeof(MapEntry) + keyLen);
    entry->hash = hashKey;
    entry->keyLen = keyLen;
    entry->value = value;
    memcpy(entry->key, key, keyLen);

    entry->next = bucket->head;
    bucket->head = entry;

    bucket->size++;
    map->size++;

    return true;
}

bool map_remove(Map* map, const void* key, size_t keyLen){
    unsigned int hashKey = hash((unsigned char*) key, keyLen);
    unsigned short bucketKey = hashKey % BUCKET_SIZE;

    MapBucket* bucket = &map->buckets[bucketKey];
    MapEntry* prev = NULL;
    MapEntry* cursor = bucket->head;
 
    while(cursor != NULL){
         if(cursor->hash == hashKey 
            &&  memcmp((unsigned char*)key, cursor->key, keyLen) == 0){
            if(prev == NULL){
                bucket->head = cursor->next;
            }else{
                prev->next = cursor->next;
            }
            free(cursor);

            bucket->size--;
            map->size--;

            return true;
        }
        prev = cursor;
        cursor = cursor->next;
    }

    return false;
}


void map_destroy(Map* map){
    free(map->buckets);
    free(map);
}
