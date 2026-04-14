"""Dynamic Programming solution for Maximum Sum Increasing Subsequence (MSIS)."""

from typing import List, Tuple


def maximum_sum_increasing_subsequence(arr: List[int]) -> Tuple[int, List[int]]:
    """
    Compute the maximum sum increasing subsequence and reconstruct the subsequence.

    DP state:
    dp[i] = maximum sum of an increasing subsequence ending at index i.

    Recurrence:
    dp[i] = max(dp[i], dp[j] + arr[i]) for all j < i with arr[j] < arr[i]

    Why this differs from LIS:
    - LIS optimizes subsequence length.
    - MSIS optimizes subsequence sum.

    Time Complexity: O(n^2)
    Space Complexity: O(n)
    """
    if not arr:
        return 0, []

    n = len(arr)
    dp = arr[:]  # Base case: subsequence containing only arr[i]
    parent = [-1] * n  # For reconstruction

    for i in range(n):
        for j in range(i):
            if arr[j] < arr[i] and dp[j] + arr[i] > dp[i]:
                dp[i] = dp[j] + arr[i]
                parent[i] = j

    max_sum = max(dp)
    end_index = dp.index(max_sum)

    # Backtrack to construct subsequence.
    subsequence: List[int] = []
    while end_index != -1:
        subsequence.append(arr[end_index])
        end_index = parent[end_index]
    subsequence.reverse()

    return max_sum, subsequence
