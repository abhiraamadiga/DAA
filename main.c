#include <stdio.h>
#include <stdlib.h>

#include "heap_range.h"
#include "line_intersection.h"
#include "msis_dp.h"
#include "utils.h"

static int read_menu_choice(void) {
    int *values = NULL;
    int count;
    count = parse_int_list("Enter your choice (1-4): ", &values);
    if (count != 1) {
        free(values);
        return -1;
    }
    {
        int choice = values[0];
        free(values);
        return choice;
    }
}

static void run_smallest_range(void) {
    IntArray *arrays = NULL;
    int k = 0;
    int start = 0;
    int end = 0;
    int ok;

    printf("\n--- Smallest Range from k Sorted Arrays (Heap) ---\n");

    if (read_yes_no("Use sample input? (y/n): ")) {
        arrays = sample_data_smallest_range(&k);
        if (arrays == NULL) {
            printf("Unable to load sample data.\n");
            return;
        }
        printf("Sample arrays loaded.\n");
    } else {
        input_k_sorted_arrays(&arrays, &k);
        if (arrays == NULL || k <= 0) {
            printf("Invalid arrays input.\n");
            return;
        }
    }

    ok = find_smallest_range(arrays, k, 1, &start, &end);
    if (ok) {
        printf("Smallest range including at least one element from each array: [%d, %d]\n", start, end);
    } else {
        printf("Could not compute the range.\n");
    }

    free_k_sorted_arrays(arrays, k);
}

static void run_line_intersection(void) {
    HorizontalSegment *horizontal = NULL;
    VerticalSegment *vertical = NULL;
    int h_count = 0;
    int v_count = 0;
    int count;

    printf("\n--- Line Segment Intersection Count (Sweep Line) ---\n");

    if (read_yes_no("Use sample input? (y/n): ")) {
        sample_data_line_intersections(&horizontal, &h_count, &vertical, &v_count);
        if (horizontal == NULL || vertical == NULL) {
            printf("Unable to load sample data.\n");
            return;
        }
        printf("Sample segments loaded.\n");
    } else {
        input_line_segments(&horizontal, &h_count, &vertical, &v_count);
        if (horizontal == NULL || vertical == NULL) {
            printf("Invalid segment input.\n");
            free(horizontal);
            free(vertical);
            return;
        }
    }

    count = count_intersections(horizontal, h_count, vertical, v_count, 1);
    printf("Total intersections: %d\n", count);

    free(horizontal);
    free(vertical);
}

static void run_msis(void) {
    int *arr = NULL;
    int n = 0;
    int *subsequence = NULL;
    int subsequence_len = 0;
    int max_sum;
    int i;

    printf("\n--- Maximum Sum Increasing Subsequence (Dynamic Programming) ---\n");

    if (read_yes_no("Use sample input? (y/n): ")) {
        sample_data_msis(&arr, &n);
        if (arr == NULL || n <= 0) {
            printf("Unable to load sample data.\n");
            return;
        }
        printf("Sample array loaded.\n");
    } else {
        n = parse_int_list("Enter array elements (space-separated): ", &arr);
        if (n <= 0 || arr == NULL) {
            printf("Invalid array input.\n");
            free(arr);
            return;
        }
    }

    max_sum = maximum_sum_increasing_subsequence(arr, n, &subsequence, &subsequence_len);
    printf("Maximum sum: %d\n", max_sum);
    printf("MSIS subsequence: ");
    for (i = 0; i < subsequence_len; i++) {
        printf("%d", subsequence[i]);
        if (i + 1 < subsequence_len) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    free(subsequence);
}

static void print_menu(void) {
    printf("\n================ DAA Mini Project ================\n");
    printf("1. Smallest Range (Heap)\n");
    printf("2. Line Intersection (Sweep Line)\n");
    printf("3. Maximum Sum Increasing Subsequence (DP)\n");
    printf("4. Exit\n");
}

int main(void) {
    while (1) {
        int choice;
        print_menu();
        choice = read_menu_choice();

        if (choice == 1) {
            run_smallest_range();
        } else if (choice == 2) {
            run_line_intersection();
        } else if (choice == 3) {
            run_msis();
        } else if (choice == 4) {
            printf("Exiting. Thank you!\n");
            break;
        } else {
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}