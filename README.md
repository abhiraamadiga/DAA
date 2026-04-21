# Design and Analysis of Algorithms Mini Project

This project is a menu-driven C application that demonstrates three important algorithm design techniques:

1. Heap-based optimization
2. Sweep line with event processing
3. Dynamic programming with solution reconstruction

The goal of this project is to show not only working implementations, but also why these approaches are better than naive methods for the same problems.

## Project Objective

The mini project solves three independent algorithmic problems that commonly appear in DAA courses and coding interviews:

1. Smallest range covering at least one element from each of k sorted arrays
2. Counting intersections between horizontal and vertical line segments
3. Maximum Sum Increasing Subsequence (MSIS)

Each module is implemented in C with clear separation between logic and input handling, and all modules are integrated through one CLI menu.

## Problem Statements and Solutions

### 1) Smallest Range from k Sorted Arrays (Heap)

#### Problem
Given k sorted arrays, find the minimum-length range [L, R] such that at least one element from every array lies in that range.

#### Why this is challenging
A brute-force approach compares many combinations across arrays and becomes expensive as k and array sizes increase.

#### Core algorithm idea
This implementation uses a min-heap to always track the current minimum selected element among arrays.

1. Insert the first element of each array into a min-heap.
2. Maintain current maximum among those selected elements.
3. The heap root gives current minimum.
4. Update best range using current minimum and current maximum.
5. Pop minimum, then push the next element from the same array.
6. Stop when one array gets exhausted (cannot cover all arrays anymore).

#### Why heap helps
The minimum can be extracted in O(log k), allowing efficient range updates while scanning candidates.

#### Complexity
- Time: O(Nk log k) where N is average elements per array
- Space: O(k)

---

### 2) Line Segment Intersection Count (Sweep Line)

#### Problem
Given:
- Horizontal segments: (x1, x2, y)
- Vertical segments: (x, y1, y2)

Count how many intersections exist.

#### Why this is challenging
Naive pairwise checking compares every horizontal with every vertical segment, leading to O(HV) or O(n^2)-style behavior.

#### Core algorithm idea (Sweep Line)
Convert geometry into events sorted by x-coordinate:

1. START event at x1 for each horizontal segment
2. END event at x2 for each horizontal segment
3. VERTICAL query event at x for each vertical segment

Maintain an active sorted list of y-values for horizontal segments currently intersecting the sweep position.

- On START: insert y in active structure
- On END: remove y
- On VERTICAL: count active y values in [y1, y2] using binary search

#### Why sweep line helps
Only relevant active horizontals are considered at each x, avoiding unnecessary pair checks.

#### Complexity
- Time: O((H + V) log(H + V) + K) where K is number of reported intersections
- Space: O(H)

---

### 3) Maximum Sum Increasing Subsequence (Dynamic Programming)

#### Problem
Given an array, find an increasing subsequence whose sum is maximum.

Example:
- Input: [1, 101, 2, 3, 100]
- Best subsequence: [1, 2, 3, 100]
- Maximum sum: 106

#### Core DP definition
Let dp[i] = maximum sum of an increasing subsequence ending at index i.

Transition:

dp[i] = max(dp[i], dp[j] + arr[i]) for all j < i with arr[j] < arr[i]

#### Reconstruction
The code stores parent links to reconstruct the actual subsequence, not only the maximum sum.

#### Complexity
- Time: O(n^2)
- Space: O(n)

## Code Structure

- main.c
	- Menu flow
	- Calls each problem module

- heap_range.c / heap_range.h
	- Heap node operations
	- Smallest range algorithm

- line_intersection.c / line_intersection.h
	- Event modeling and sorting
	- Sweep-line processing

- msis_dp.c / msis_dp.h
	- DP table construction
	- Parent tracking and subsequence reconstruction

- utils.c / utils.h
	- Input parsing helpers
	- Memory-safe utility routines
	- Built-in sample test cases

## Input and Output Design

The CLI supports two modes for each problem:

1. Sample mode (quick demonstration)
2. Manual mode (user-provided custom data)

For each selected problem, the application prints intermediate details (where applicable) and final answer in readable format.

## Build and Run

### Compile

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c heap_range.c line_intersection.c msis_dp.c utils.c -o daa_project
```

### Run

Linux/macOS:

```bash
./daa_project
```

Windows PowerShell:

```powershell
.\daa_project.exe
```

## Demo Flow (Recommended for Presentation)

1. Run executable.
2. Choose option 1, then sample input.
3. Explain heap behavior and final smallest range.
4. Choose option 2, then sample input.
5. Explain events (START, VERTICAL, END) and intersection count.
6. Choose option 3, then sample input.
7. Explain DP table concept and reconstructed subsequence.
8. Choose option 4 to exit.

## Demo Walkthrough (Problem -> Solution -> How Solution Came)

Use this section while presenting. You can read it directly in viva/demo format.

### Demo 1: Smallest Range from k Sorted Arrays

Problem:
We are given k sorted arrays. We must find the smallest interval [L, R] such that at least one element from every array lies inside this interval.

Solution:
Use a min-heap to track one current element from each array, and maintain the current maximum among them.

How the solution came:
1. If we pick one element from each array, those k elements define a range from minimum to maximum.
2. To make the range smaller, we should move forward from the current minimum element, because increasing minimum can shrink width.
3. A min-heap gives that minimum quickly each time.
4. After popping that minimum, we push the next element from the same array, so coverage from all arrays is preserved.
5. We keep updating the best range seen so far.
6. When one array is exhausted, we cannot maintain coverage from all arrays, so we stop.

Why this is correct intuitively:
At every step, the only useful move is to advance the array that currently contributes the minimum boundary.

---

### Demo 2: Line Segment Intersections

Problem:
Given horizontal and vertical line segments, count how many intersections occur.

Solution:
Use sweep line with events sorted by x-coordinate and maintain active horizontal y-values.

How the solution came:
1. Naive method checks every horizontal with every vertical, which is too slow for larger inputs.
2. Instead, sweep from left to right on x-axis and process only relevant segments.
3. For each horizontal segment, create START(x1) and END(x2) events.
4. For each vertical segment, create a VERTICAL query event at x.
5. Maintain all currently active horizontal y-values in sorted order.
6. On a VERTICAL event, count active y-values in [y1, y2] using binary search.
7. Add those counts to total intersections.

Why this is correct intuitively:
At position x, only horizontals that have started and not ended can intersect a vertical at that x. So active set + range query is exactly what we need.

---

### Demo 3: Maximum Sum Increasing Subsequence (MSIS)

Problem:
Find an increasing subsequence with maximum possible sum.

Solution:
Use dynamic programming and parent links.

How the solution came:
1. For each index i, define dp[i] as best sum of an increasing subsequence ending at i.
2. Initially dp[i] = arr[i] (subsequence containing only that element).
3. For each pair j < i, if arr[j] < arr[i], then arr[i] can extend subsequence ending at j.
4. So candidate sum is dp[j] + arr[i]. Keep the maximum.
5. Track parent[i] = j whenever dp[i] improves.
6. After filling DP, the maximum dp[i] is answer sum.
7. Follow parent links backward to reconstruct actual subsequence.

Why this is correct intuitively:
Every increasing subsequence ending at i must come from some earlier valid j. DP evaluates all such j and stores the best one.

## Quick Viva Script (30-45 seconds each)

1. Problem statement in one line.
2. Why naive is expensive.
3. Data structure/paradigm used.
4. Core idea in 4-6 steps.
5. Time and space complexity.
6. One-line correctness intuition.

## Educational Value

This project demonstrates key DAA learning outcomes:

1. Choosing the right data structure for optimization (heap)
2. Reducing geometric query complexity with event-based sweeping
3. Turning exponential subsequence search into polynomial DP
4. Reconstructing solutions, not only computing objective values

## Notes

- Code is written in standard C (C11-compatible).
- Memory allocation and deallocation are handled in module logic and utility helpers.
- Verbose prints are included in critical algorithms for easier viva explanation.
