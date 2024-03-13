#include <stdlib.h>
#include <stdio.h>
#include "wquf.h"

struct weighted_quick_union_find *wquf_init(int n)
{
        // allocate the struct
        struct weighted_quick_union_find *wquf;
        wquf = malloc(sizeof(struct weighted_quick_union_find));
        if (!wquf) return NULL;

        // initialize the members of our struct
        wquf->count = n;
        wquf->orig_arr_sz = n;
        wquf->parent = malloc(sizeof(int)*n);
        wquf->size = malloc(sizeof(int)*n);
        if (!wquf->parent || !wquf->size) {
                printf("ERROR: could not allocate memobry for wquf with size %d", n);
                exit(1);
        }

        // initial values for our parent and size arrays
        for (int i = 0; i < n; i++) {
                wquf->parent[i] = i;
                wquf->size[i] = 1; // initial size of 1 for each p since they are their own "root" in the algorithm
        }
        return wquf;
}

void wquf_destroy(struct weighted_quick_union_find *wquf)
{
        // free struct members first to prevent mem leak
        free(wquf->parent);
        free(wquf->size);
        free(wquf);
        printf("INFO: all memory is freed for wquf\n");
}

unsigned int wquf_count(struct weighted_quick_union_find *wquf)
{
        return wquf->count;
}

unsigned int wquf_find(struct weighted_quick_union_find *wquf, int p)
{
        // validate tthat the element to search for is a valid index
        int err = wquf_validate(wquf, p);
        if (!err) {
                printf("ERROR: index must be between 0 and %zu. index passed was: %d\n", wquf->orig_arr_sz-1, p);
                exit(1);
        }

        /* search the parent array until we find the root (parent) value of the p integer
           p        0  1  2  3  4  5  6  7  8  9
        ----------------------------------------
        parent[p]   0  9  6  5  4  2  6  1  0  5
        */
        while (p != wquf->parent[p])
                p = wquf->parent[p];
        return p;
}

bool wquf_validate(struct weighted_quick_union_find *wquf, int p)
{
        // index cannot be negative and index must be <= n-1  (since it is 0-indexed)
        if (p < 0 || p >= wquf->orig_arr_sz)  {
                return false;
        }
        return true; 
}

bool wquf_connected(struct weighted_quick_union_find *wquf, int p, int q)
{
        return wquf_find(wquf, p) == wquf_find(wquf, q);
}

void wquf_union(struct weighted_quick_union_find *wquf, int p, int q)
{
        int root_p;
        int root_q;
 
        root_p = wquf_find(wquf, p);
        root_q = wquf_find(wquf, q);
        if (root_p == root_q) return;

        // make smaller root (root with less elements) point to larger one
        if (wquf->size[root_p] < wquf->size[root_q]) {
                wquf->parent[root_p] = root_q;
                wquf->size[root_q] += wquf->size[root_p];
        }
        else {
                wquf->parent[root_q] = root_p;
                wquf->size[root_p] += wquf->size[root_q];
        }
        wquf->count--;
}
