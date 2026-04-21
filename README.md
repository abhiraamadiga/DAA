# Design and Analysis of Algorithms - Mini Project (C Version)

This project implements three classic algorithmic problems in pure C with a menu-driven CLI.

## Project Structure

- `main.c` - entry point with menu-driven interface
- `heap_range.c` / `heap_range.h` - smallest range covering at least one element from each sorted array
- `line_intersection.c` / `line_intersection.h` - sweep-line based intersection counting
- `msis_dp.c` / `msis_dp.h` - dynamic programming for maximum sum increasing subsequence
- `utils.c` / `utils.h` - input parsing, memory helpers, and sample test data

## Problem 1: Smallest Range from k Sorted Arrays (Heap)

### Problem
Given `k` sorted arrays, find the smallest range that includes at least one element from each array.

### Why Heap is Used
A min-heap always gives the current minimum among selected elements from each array in `O(log k)` time, making range updates efficient.

### Core Idea
1. Insert first element of each array into min-heap.
2. Track current maximum among inserted elements.
3. Pop minimum and update best range.
4. Push next element from the same array.
5. Stop when any array is exhausted.

### Complexity
- Heap approach: `O(nk log k)`

## Problem 2: Line Segment Intersections (Sweep Line)

### Problem
Given horizontal and vertical line segments, count how many intersections exist.

### Why Sweep Line is Efficient
Instead of checking every pair (`O(n^2)`), sweep-line processes x-coordinate events and keeps only currently active horizontal segments.

### Event Types
- `START` (horizontal segment begins)
- `VERTICAL` (query active horizontals in y-range)
- `END` (horizontal segment ends)

### Complexity
- Sweep-line with sorting + binary search: `O((H + V) log(H + V) + K)`

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

### Complexity
- Time: `O(n^2)`
- Space: `O(n)`

## How to Build and Run

1. Open terminal in project folder.
2. Compile:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c heap_range.c line_intersection.c msis_dp.c utils.c -o daa_project
```

3. Run:

```bash
./daa_project
```

On Windows (PowerShell), run:

```powershell
.\daa_project.exe
```

4. Use menu options:
- 1: Smallest Range (Heap)
- 2: Line Intersection (Sweep Line)
- 3: MSIS (DP)
- 4: Exit
