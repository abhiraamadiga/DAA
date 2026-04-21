#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 2048

static int read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }
    return 1;
}

static void trim_newline(char *buffer) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

static int read_int_from_prompt(const char *prompt) {
    char line[INPUT_BUFFER_SIZE];
    char *endptr;
    long value;

    while (1) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            return 0;
        }

        value = strtol(line, &endptr, 10);
        if (endptr == line) {
            printf("Invalid integer. Try again.\n");
            continue;
        }

        while (*endptr != '\0') {
            if (!isspace((unsigned char)*endptr)) {
                break;
            }
            endptr++;
        }

        if (*endptr == '\0') {
            return (int)value;
        }

        printf("Invalid input. Enter only one integer.\n");
    }
}

bool read_yes_no(const char *prompt) {
    char line[INPUT_BUFFER_SIZE];
    while (1) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            return false;
        }
        trim_newline(line);

        if (line[0] == 'y' || line[0] == 'Y') {
            return true;
        }
        if (line[0] == 'n' || line[0] == 'N') {
            return false;
        }

        printf("Please enter y or n.\n");
    }
}

int parse_int_list(const char *prompt, int **out_values) {
    char line[INPUT_BUFFER_SIZE];
    int capacity = 8;
    int count = 0;
    int *values;
    char *token;

    if (out_values == NULL) {
        return 0;
    }

    values = (int *)malloc((size_t)capacity * sizeof(int));
    if (values == NULL) {
        return 0;
    }

    while (1) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            free(values);
            *out_values = NULL;
            return 0;
        }

        trim_newline(line);
        token = strtok(line, " \t");
        count = 0;

        while (token != NULL) {
            char *endptr;
            long value = strtol(token, &endptr, 10);
            if (*endptr != '\0') {
                count = -1;
                break;
            }

            if (count >= capacity) {
                int *grown;
                capacity *= 2;
                grown = (int *)realloc(values, (size_t)capacity * sizeof(int));
                if (grown == NULL) {
                    free(values);
                    *out_values = NULL;
                    return 0;
                }
                values = grown;
            }

            values[count++] = (int)value;
            token = strtok(NULL, " \t");
        }

        if (count > 0) {
            *out_values = values;
            return count;
        }

        if (count == -1) {
            printf("Invalid list. Enter only integers separated by spaces.\n");
        } else {
            printf("Please enter at least one integer.\n");
        }
    }
}

void input_k_sorted_arrays(IntArray **out_arrays, int *out_k) {
    int i;
    int k;
    IntArray *arrays;

    if (out_arrays == NULL || out_k == NULL) {
        return;
    }

    k = read_int_from_prompt("Enter number of arrays (k): ");
    while (k <= 0) {
        printf("k must be positive.\n");
        k = read_int_from_prompt("Enter number of arrays (k): ");
    }

    arrays = (IntArray *)calloc((size_t)k, sizeof(IntArray));
    if (arrays == NULL) {
        *out_arrays = NULL;
        *out_k = 0;
        return;
    }

    for (i = 0; i < k; i++) {
        char prompt[128];
        snprintf(prompt, sizeof(prompt), "Enter sorted elements of array %d: ", i + 1);
        arrays[i].size = parse_int_list(prompt, &arrays[i].data);
        if (arrays[i].size <= 0 || arrays[i].data == NULL) {
            free_k_sorted_arrays(arrays, i + 1);
            *out_arrays = NULL;
            *out_k = 0;
            return;
        }
    }

    *out_arrays = arrays;
    *out_k = k;
}

void free_k_sorted_arrays(IntArray *arrays, int k) {
    int i;
    if (arrays == NULL) {
        return;
    }
    for (i = 0; i < k; i++) {
        free(arrays[i].data);
    }
    free(arrays);
}

void input_line_segments(
    HorizontalSegment **out_horizontal,
    int *out_h_count,
    VerticalSegment **out_vertical,
    int *out_v_count
) {
    int i;
    int h;
    int v;
    HorizontalSegment *horizontal;
    VerticalSegment *vertical;

    if (out_horizontal == NULL || out_h_count == NULL ||
        out_vertical == NULL || out_v_count == NULL) {
        return;
    }

    h = read_int_from_prompt("Enter number of horizontal segments: ");
    while (h < 0) {
        printf("Count cannot be negative.\n");
        h = read_int_from_prompt("Enter number of horizontal segments: ");
    }

    horizontal = (HorizontalSegment *)malloc((size_t)(h > 0 ? h : 1) * sizeof(HorizontalSegment));
    if (horizontal == NULL) {
        *out_horizontal = NULL;
        *out_h_count = 0;
        *out_vertical = NULL;
        *out_v_count = 0;
        return;
    }

    printf("Enter each horizontal segment as: x1 x2 y\n");
    for (i = 0; i < h; i++) {
        int *values = NULL;
        char prompt[64];
        int n;
        snprintf(prompt, sizeof(prompt), "H%d: ", i + 1);

        n = parse_int_list(prompt, &values);
        while (n != 3) {
            printf("Please enter exactly 3 integers.\n");
            free(values);
            values = NULL;
            n = parse_int_list(prompt, &values);
        }

        horizontal[i].x1 = values[0];
        horizontal[i].x2 = values[1];
        horizontal[i].y = values[2];
        free(values);
    }

    v = read_int_from_prompt("Enter number of vertical segments: ");
    while (v < 0) {
        printf("Count cannot be negative.\n");
        v = read_int_from_prompt("Enter number of vertical segments: ");
    }

    vertical = (VerticalSegment *)malloc((size_t)(v > 0 ? v : 1) * sizeof(VerticalSegment));
    if (vertical == NULL) {
        free(horizontal);
        *out_horizontal = NULL;
        *out_h_count = 0;
        *out_vertical = NULL;
        *out_v_count = 0;
        return;
    }

    printf("Enter each vertical segment as: x y1 y2\n");
    for (i = 0; i < v; i++) {
        int *values = NULL;
        char prompt[64];
        int n;
        snprintf(prompt, sizeof(prompt), "V%d: ", i + 1);

        n = parse_int_list(prompt, &values);
        while (n != 3) {
            printf("Please enter exactly 3 integers.\n");
            free(values);
            values = NULL;
            n = parse_int_list(prompt, &values);
        }

        vertical[i].x = values[0];
        vertical[i].y1 = values[1];
        vertical[i].y2 = values[2];
        free(values);
    }

    *out_horizontal = horizontal;
    *out_h_count = h;
    *out_vertical = vertical;
    *out_v_count = v;
}

IntArray *sample_data_smallest_range(int *out_k) {
    IntArray *arrays;

    if (out_k == NULL) {
        return NULL;
    }

    *out_k = 3;
    arrays = (IntArray *)calloc(3, sizeof(IntArray));
    if (arrays == NULL) {
        *out_k = 0;
        return NULL;
    }

    arrays[0].size = 5;
    arrays[1].size = 5;
    arrays[2].size = 5;

    arrays[0].data = (int *)malloc(5 * sizeof(int));
    arrays[1].data = (int *)malloc(5 * sizeof(int));
    arrays[2].data = (int *)malloc(5 * sizeof(int));

    if (arrays[0].data == NULL || arrays[1].data == NULL || arrays[2].data == NULL) {
        free_k_sorted_arrays(arrays, 3);
        *out_k = 0;
        return NULL;
    }

    {
        int a0[] = {4, 7, 9, 12, 15};
        int a1[] = {0, 8, 10, 14, 20};
        int a2[] = {6, 12, 16, 30, 50};
        memcpy(arrays[0].data, a0, sizeof(a0));
        memcpy(arrays[1].data, a1, sizeof(a1));
        memcpy(arrays[2].data, a2, sizeof(a2));
    }

    return arrays;
}

void sample_data_line_intersections(
    HorizontalSegment **out_horizontal,
    int *out_h_count,
    VerticalSegment **out_vertical,
    int *out_v_count
) {
    HorizontalSegment *horizontal;
    VerticalSegment *vertical;

    if (out_horizontal == NULL || out_h_count == NULL ||
        out_vertical == NULL || out_v_count == NULL) {
        return;
    }

    *out_h_count = 3;
    *out_v_count = 3;

    horizontal = (HorizontalSegment *)malloc(3 * sizeof(HorizontalSegment));
    vertical = (VerticalSegment *)malloc(3 * sizeof(VerticalSegment));
    if (horizontal == NULL || vertical == NULL) {
        free(horizontal);
        free(vertical);
        *out_horizontal = NULL;
        *out_vertical = NULL;
        *out_h_count = 0;
        *out_v_count = 0;
        return;
    }

    horizontal[0] = (HorizontalSegment){1, 5, 2};
    horizontal[1] = (HorizontalSegment){2, 7, 4};
    horizontal[2] = (HorizontalSegment){6, 9, 1};

    vertical[0] = (VerticalSegment){3, 1, 5};
    vertical[1] = (VerticalSegment){6, 0, 4};
    vertical[2] = (VerticalSegment){8, 1, 3};

    *out_horizontal = horizontal;
    *out_vertical = vertical;
}

void sample_data_msis(int **out_arr, int *out_n) {
    int *arr;
    int sample[] = {1, 101, 2, 3, 100, 4, 5};

    if (out_arr == NULL || out_n == NULL) {
        return;
    }

    arr = (int *)malloc((size_t)7 * sizeof(int));
    if (arr == NULL) {
        *out_arr = NULL;
        *out_n = 0;
        return;
    }

    memcpy(arr, sample, sizeof(sample));
    *out_arr = arr;
    *out_n = 7;
}