#ifndef FILTER_H
#define FILTER_H

#include<stdlib.h>

typedef struct {
    char *cursor;
    size_t remaining;
} FilterHandle;


typedef enum FilterHandleResponse{
    FILTER_HANDLER_SUCCESS = 0,
    FLITER_HANDLER_NOT_ENOUGH_REMAINING  = -1
}FilterHandleResponse;

typedef int (*FilterHandler)(FilterHandle* handle);

typedef struct FilterChainNode {
    FilterHandler handler;
    struct FilterChainNode* next;
} FilterChainNode;

#endif
