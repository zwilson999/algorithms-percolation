#define CONFIDENCE_95 1.96

#include "percolation.h"
#include "percolation_stats.h"
#include "uniform_random.h"
#include "stats.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct percolation_stats* percolation_stats_init(int n, int trials)
{
        if (n <= 0 || trials <= 0) {
                printf("INFO: n and num_trials must be > 0");
                exit(1);
        }
        
        struct percolation_stats *prc_stats;
        prc_stats = malloc(sizeof(struct percolation_stats));
        if (!prc_stats) return NULL;

        prc_stats->results = malloc(sizeof(double)*trials);
        if (!prc_stats->results) {
                printf("ERROR: could not allocate memory for percolation_stats struct with n = %d, #trials = %d", n, trials);
                exit(1);
        }
        prc_stats->n = n;
        prc_stats->num_trials = trials;
        return prc_stats;
}

void percolation_stats_destroy(struct percolation_stats *prc_stats)
{
        free(prc_stats->results);
        free(prc_stats);
        printf("INFO: all memory is freed for percolation stats\n");
}

void percolation_stats_run(struct percolation_stats *prc_stats)
{
        int rand_row;
        int rand_col;
        int grid_size;
        int flat_grid_size;
        int num_open_sites;
        struct percolation *prc;

        // initialize
        grid_size = prc_stats->n;
        flat_grid_size = grid_size*grid_size;

        // compute metrics for all trials
        // initialize seed for random operations
        srand(time(NULL)); 
        for (int i = 0; i < prc_stats->num_trials; i++) {
               prc = percolation_init(grid_size);
               while (!percolation_percolates(prc)) {

                       // select random row and column values
                       rand_row = uniform_random(1, grid_size+1);
                       rand_col = uniform_random(1, grid_size+1);
                       printf("INFO: opening row: %d, col: %d\n", rand_row, rand_col);
                       percolation_open(prc, rand_row, rand_col);
               }
               num_open_sites = prc->num_open_sites;
               double result = (double) num_open_sites/(flat_grid_size);
               prc_stats->results[i] = result; // append to results array
        }

        // compute summary statistics and return
        prc_stats->mean = percolation_stats_mean(prc_stats);
        prc_stats->std_deviation = percolation_stats_std_deviation(prc_stats);
        prc_stats->confidence_interval_lower = percolation_stats_confidence_lower(prc_stats);
        prc_stats->confidence_interval_upper = percolation_stats_confidence_upper(prc_stats);
}

double percolation_stats_mean(struct percolation_stats *prc_stats)
{
        return mean(prc_stats->results, prc_stats->num_trials);
}

double percolation_stats_std_deviation(struct percolation_stats *prc_stats)
{
        return std_dev(prc_stats->results, prc_stats->num_trials);
}

double percolation_stats_confidence_upper(struct percolation_stats *prc_stats)
{
        return percolation_stats_mean(prc_stats) + ((CONFIDENCE_95*percolation_stats_std_deviation(prc_stats)) / sqrt(prc_stats->num_trials));
}

double percolation_stats_confidence_lower(struct percolation_stats *prc_stats)
{
        return percolation_stats_mean(prc_stats) - ((CONFIDENCE_95*percolation_stats_std_deviation(prc_stats)) / sqrt(prc_stats->num_trials));
}
