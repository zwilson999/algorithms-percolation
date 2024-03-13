#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "uniform_random.h"

int uniform_random(int a, int b)
{
        if ( (b <= a) || ( (long) b - a >= INT_MAX)) {
                printf("ERROR: random uniform has invalid range a: %d, b: %d", a, b);
                exit(1);
        }
        return rand() % (b-a) + a;
}
