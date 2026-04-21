#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

typedef struct {
    int *data;
    int size;
} IntArray;

typedef struct {
    int x1;
    int x2;
    int y;
} HorizontalSegment;

typedef struct {
    int x;
    int y1;
    int y2;
} VerticalSegment;

bool read_yes_no(const char *prompt);
int parse_int_list(const char *prompt, int **out_values);

void input_k_sorted_arrays(IntArray **out_arrays, int *out_k);
void free_k_sorted_arrays(IntArray *arrays, int k);

void input_line_segments(
    HorizontalSegment **out_horizontal,
    int *out_h_count,
    VerticalSegment **out_vertical,
    int *out_v_count
);

IntArray *sample_data_smallest_range(int *out_k);
void sample_data_line_intersections(
    HorizontalSegment **out_horizontal,
    int *out_h_count,
    VerticalSegment **out_vertical,
    int *out_v_count
);
void sample_data_msis(int **out_arr, int *out_n);

#endif