#include <stdlib.h>
#include <stdio.h>
#include "percolation_stats.h"

int main(int argc, char *argv[])
{
        // stop early if not enough args
        if (argc < 3) return 1;

        // extract user args
        int n;
        int num_trials;
        struct percolation_stats *prc_stats;
        n = atoi(argv[1]);
        num_trials = atoi(argv[2]);
        printf("INFO: running simulation for size=%d, and #trials=%d\n", n, num_trials);

        prc_stats = percolation_stats_init(n, num_trials); 
        percolation_stats_run(prc_stats);

        printf("INFO: mean = %f\n", prc_stats->mean);
        printf("INFO: stddev = %f\n", prc_stats->std_deviation);
        printf("INFO: 95%% confidence interval =  (%f, %f)\n", prc_stats->confidence_interval_lower, prc_stats->confidence_interval_upper);
        percolation_stats_destroy(prc_stats);
        return 0;
}
