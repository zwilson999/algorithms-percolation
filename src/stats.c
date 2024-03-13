#include <math.h>
#include "stats.h"
// #include <stdio.h>

double mean(double arr[], int arr_len)
{
        if (arr_len == 0) return NAN;

        double sum = 0.0;
        for (int i = 0; i < arr_len; i++) {
                sum += arr[i];
        }
        return sum/arr_len;
}

double var(double arr[], int arr_len)
{
       if (arr_len == 0) return NAN;
       double avg = 0.0;
       double sum = 0.0;

       avg = mean(arr, arr_len);
       for (int i = 0; i < arr_len; i++)
               sum += (arr[i] - avg) * (arr[i] - avg);
       return sum / (arr_len-1);
}

double std_dev(double arr[], int arr_len)
{
        return sqrt(var(arr, arr_len));
}

