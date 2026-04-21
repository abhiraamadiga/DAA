#include "msis_dp.h"

#include <stdlib.h>

int maximum_sum_increasing_subsequence(
    const int *arr,
    int n,
    int **out_subsequence,
    int *out_subsequence_length
) {
    int i;
    int j;
    int max_sum;
    int end_index;
    int *dp;
    int *parent;
    int *subsequence;
    int length = 0;
    int walk;

    if (out_subsequence == NULL || out_subsequence_length == NULL) {
        return 0;
    }

    *out_subsequence = NULL;
    *out_subsequence_length = 0;

    if (arr == NULL || n <= 0) {
        return 0;
    }

    dp = (int *)malloc((size_t)n * sizeof(int));
    parent = (int *)malloc((size_t)n * sizeof(int));
    if (dp == NULL || parent == NULL) {
        free(dp);
        free(parent);
        return 0;
    }

    for (i = 0; i < n; i++) {
        dp[i] = arr[i];
        parent[i] = -1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + arr[i] > dp[i]) {
                dp[i] = dp[j] + arr[i];
                parent[i] = j;
            }
        }
    }

    max_sum = dp[0];
    end_index = 0;
    for (i = 1; i < n; i++) {
        if (dp[i] > max_sum) {
            max_sum = dp[i];
            end_index = i;
        }
    }

    walk = end_index;
    while (walk != -1) {
        length++;
        walk = parent[walk];
    }

    subsequence = (int *)malloc((size_t)length * sizeof(int));
    if (subsequence == NULL) {
        free(dp);
        free(parent);
        return 0;
    }

    walk = end_index;
    for (i = length - 1; i >= 0; i--) {
        subsequence[i] = arr[walk];
        walk = parent[walk];
    }

    *out_subsequence = subsequence;
    *out_subsequence_length = length;

    free(dp);
    free(parent);
    return max_sum;
}