#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <stdbool.h>
#include "wquf.h"

struct percolation {
        int num_open_sites;
        int grid_size;
        int flat_grid_size;

        // virtual top and bottom we will use to see if top and bottom are connected
        int virtual_top;
        int virtual_bottom;

        bool *grid;
        struct weighted_quick_union_find *wquf_grid;
        struct weighted_quick_union_find *wquf_full;
};

struct percolation * percolation_init(int n);
void percolation_destroy(struct percolation *p);
void percolation_open(struct percolation *p, int row, int col);
int percolation_flatten(int grid_size, int row, int col);
bool percolation_is_open(struct percolation *p, int row, int col);
bool percolation_is_valid(int grid_size, int row, int col);
bool percolation_is_full(struct percolation *p, int row, int col);
bool percolation_percolates(struct percolation *p);

#endif
