#ifndef WQUF_H
#define WQUF_H

#include <stdbool.h>
#include <stddef.h>

// struct object for implementing the weighted quick union find algorithm
struct weighted_quick_union_find {
        unsigned int count; // number of elements
        size_t orig_arr_sz;
        int *parent; // for parent array
        int *size; // for size array
};

// allocator
struct weighted_quick_union_find * wquf_init(int n);

// deallocator
void wquf_destroy(struct weighted_quick_union_find *wquf);

unsigned int wquf_count(struct weighted_quick_union_find *wquf); 
unsigned int wquf_find(struct weighted_quick_union_find *wquf, int p);
bool wquf_validate(struct weighted_quick_union_find *wquf, int p);
bool wquf_connected(struct weighted_quick_union_find *wquf, int p, int q);
void wquf_union(struct weighted_quick_union_find *wquf, int p, int q);

#endif
