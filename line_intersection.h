#ifndef LINE_INTERSECTION_H
#define LINE_INTERSECTION_H

#include "utils.h"

int count_intersections(
    const HorizontalSegment *horizontal_segments,
    int h_count,
    const VerticalSegment *vertical_segments,
    int v_count,
    int verbose
);

#endif