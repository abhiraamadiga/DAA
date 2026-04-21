#ifndef HEAP_RANGE_H
#define HEAP_RANGE_H

#include "utils.h"

int find_smallest_range(
    const IntArray *arrays,
    int k,
    int verbose,
    int *out_start,
    int *out_end
);

#endif