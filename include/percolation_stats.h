#ifndef PERCOLATION_STATS_H
#define PERCOLATION_STATS_H

struct percolation_stats {
        int n;
        int num_trials;
        double *results;
        double mean;
        double std_deviation;
        double confidence_interval_lower;
        double confidence_interval_upper;
};

struct percolation_stats* percolation_stats_init(int n, int trials);
void percolation_stats_destroy(struct percolation_stats *prc_stats);
void percolation_stats_run(struct percolation_stats *prc_stats);
double percolation_stats_confidence_lower(struct percolation_stats *prc_stats);
double percolation_stats_confidence_upper(struct percolation_stats *prc_stats);
double percolation_stats_mean(struct percolation_stats *prc_stats);
double percolation_stats_std_deviation(struct percolation_stats *prc_stats);

#endif
