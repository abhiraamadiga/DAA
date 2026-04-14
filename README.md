# Design and Analysis of Algorithms - Mini Project

This project implements three classic algorithmic problems with a menu-driven CLI.

## Project Structure

- `main.py` - entry point with menu-driven interface
- `heap_range.py` - smallest range covering at least one element from each sorted array
- `line_intersection.py` - sweep-line based intersection counting
- `msis_dp.py` - dynamic programming for maximum sum increasing subsequence
- `utils.py` - input parsing and sample test data

## Problem 1: Smallest Range from k Sorted Arrays (Heap)

### Problem
Given `k` sorted arrays, find the smallest range that includes at least one element from each array.

### Why Heap is Used
A min-heap always gives the current minimum among the selected elements from each array in `O(log k)` time. This makes range updates efficient while moving one pointer at a time.

### Core Idea
1. Insert first element of each array into min-heap.
2. Track current maximum among inserted elements.
3. Pop minimum and update best range.
4. Push next element from the same array.
5. Stop when any array is exhausted.

### Complexity
- Heap approach: `O(nk log k)`
- Brute force (merge + sort + window): `O(nk log(nk))`

## Problem 2: Line Segment Intersections (Sweep Line)

### Problem
Given horizontal and vertical line segments, count how many intersections exist.

### Why Sweep Line is Efficient
Instead of checking every pair (`O(n^2)`), sweep line processes geometry by x-coordinate events and keeps only currently relevant horizontal segments active.

### Event Types
- `START` (horizontal segment begins)
- `VERTICAL` (query active horizontals in y-range)
- `END` (horizontal segment ends)

### Complexity
- Sweep-line with binary search operations: `O(n log n)`
- Naive pairwise checking: `O(n^2)`

## Problem 3: Maximum Sum Increasing Subsequence (MSIS)

### Problem
Find an increasing subsequence with maximum total sum.

Example:
- Input: `[1, 101, 2, 3, 100]`
- Output sum: `106` (subsequence `[1, 2, 3, 100]`)

### DP State
- `dp[i]` = maximum sum of increasing subsequence ending at index `i`

### Recurrence
- `dp[i] = max(dp[i], dp[j] + arr[i])` for all `j < i` with `arr[j] < arr[i]`

### LIS vs MSIS
- LIS: maximize subsequence length
- MSIS: maximize subsequence sum

### Complexity
- Time: `O(n^2)`
- Space: `O(n)`

## How to Run

1. Open terminal in project folder.
2. Run:

```bash
python main.py
```

3. Use menu options:
- 1: Smallest Range (Heap)
- 2: Line Intersection (Sweep Line)
- 3: MSIS (DP)
- 4: Exit

## Viva-Focused Notes

- Heap helps track smallest current element quickly while preserving k-way progression.
- Sweep line reduces unnecessary checks by considering only active horizontal segments.
- MSIS extends LIS-style DP but changes optimization target from length to sum.
