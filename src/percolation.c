#include "percolation.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct percolation *percolation_init(int n)
{
        // n must be > 0
        if (n <= 0) {
                printf("ERROR: size of grid must be NxN where N > 0");
                exit(1);
        }

        struct percolation *prc;
        prc = malloc(sizeof(struct percolation));
        if (!prc)  {
                printf("ERROR: could not allocate struct");
                exit(1);
        }

        // allocate 2D matrix as 1D array 
        // and set all values to false via calloc
        prc->grid = calloc((n*n), sizeof(bool));
        if (!prc->grid) {
                printf("ERROR: could not allocate grid of size %d", n);
                exit(1);
        }

        // set constants
        prc->grid_size = n;
        prc->flat_grid_size = n*n;
        prc->num_open_sites = 0;

        // create virtual top and bottom nodes to indicate if system is full
        // in any of the top or bottom sites of the grid
        prc->virtual_top = prc->flat_grid_size;
        prc->virtual_bottom = prc->flat_grid_size+1;
        
        // initialize two weighted quick union finds
        prc->wquf_grid = wquf_init(prc->flat_grid_size+2);
        prc->wquf_full = wquf_init(prc->flat_grid_size+1);
        
        return prc;
}

void percolation_destroy(struct percolation *prc)
{
        // deallocate 2d grid
        free(prc->grid);
        
        // deallocate our wquf structures
        wquf_destroy(prc->wquf_grid);
        wquf_destroy(prc->wquf_full);
        
        // deallocate struct
        free(prc);
}

void percolation_open(struct percolation *prc, int row, int col)
{
        // check if site is already open
        if (percolation_is_open(prc, row, col)) return;

        // ensure the row or column values given are within our grid's range
        if (!percolation_is_valid(prc->grid_size, row, col)) {
                printf("ERROR: index %d, %d is invalid within the "
                       "grid range of size %dx%d", 
                       row, col, prc->grid_size, prc->grid_size);
                exit(1);
        }

        // flatten into 1D representation
        int flattened;
        flattened = percolation_flatten(prc->grid_size, row, col);

        // open the site and increment open site counter
        prc->grid[flattened] = true;
        prc->num_open_sites++;

        // if the site is in the first row, connect it to the virtual top
        if (row == 1) {
                wquf_union(prc->wquf_grid, prc->virtual_top, flattened);
                wquf_union(prc->wquf_full, prc->virtual_top, flattened);
        }
        
        // if site is in the bottom row, connect it to the bottom
        if (row == prc->grid_size) {
                wquf_union(prc->wquf_grid, prc->virtual_bottom, flattened);
        }

        // open to the left
        if (percolation_is_valid(prc->grid_size, row, col-1) &&
            percolation_is_open(prc, row, col-1))
        {
                wquf_union(prc->wquf_grid, flattened, percolation_flatten(prc->grid_size, row, col-1));
                wquf_union(prc->wquf_full, flattened, percolation_flatten(prc->grid_size, row, col-1));
        }
        
        // open to the right
        if (percolation_is_valid(prc->grid_size, row, col+1) &&
            percolation_is_open(prc, row, col+1))
        {
                wquf_union(prc->wquf_grid, flattened, percolation_flatten(prc->grid_size, row, col+1));
                wquf_union(prc->wquf_full, flattened, percolation_flatten(prc->grid_size, row, col+1));
        }

        // open above
        if (percolation_is_valid(prc->grid_size, row-1, col) &&
            percolation_is_open(prc, row-1, col))
        {
                wquf_union(prc->wquf_grid, flattened, percolation_flatten(prc->grid_size, row-1, col));
                wquf_union(prc->wquf_full, flattened, percolation_flatten(prc->grid_size, row-1, col));
        }

        // open below
        if (percolation_is_valid(prc->grid_size, row+1, col) &&
            percolation_is_open(prc, row+1, col))
        {
                wquf_union(prc->wquf_grid, flattened, percolation_flatten(prc->grid_size, row+1, col));
                wquf_union(prc->wquf_full, flattened, percolation_flatten(prc->grid_size, row+1, col));
        }
}

int percolation_flatten(int grid_size, int row, int col)
{
        // transform row, column indices into flattened array representation
        // for given 2d grid size
        return (row-1)*grid_size+(col-1);
}

// check if the grid value is open
bool percolation_is_open(struct percolation *prc, int row, int col)
{
        if (!percolation_is_valid(prc->grid_size, row, col)) exit(1); 

        // use pointer arithmetic of row * size + col
        // remember row and col are 1-indexed by convention from user arguments
        // so we need to shift them by 1 each time we use them !
        return prc->grid[(row-1)*prc->grid_size+(col-1)];
}

bool percolation_is_valid(int grid_size, int row, int col)
{
        return (row >= 1 &&
                row <= grid_size &&
                col >= 1 &&
                col <= grid_size);
}

bool percolation_is_full(struct percolation *prc, int row, int col)
{
        if (!percolation_is_valid(prc->grid_size, row, col)) return false;
        return (wquf_find(prc->wquf_full, prc->virtual_top) == 
                wquf_find(prc->wquf_full, percolation_flatten(prc->grid_size, row, col)-1));
}

bool percolation_percolates(struct percolation *prc)
{
        return wquf_find(prc->wquf_grid, prc->virtual_top) == wquf_find(prc->wquf_grid, prc->virtual_bottom);
}
