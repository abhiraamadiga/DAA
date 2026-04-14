"""Heap-based solution for the smallest range covering at least one element from each sorted array."""

from dataclasses import dataclass
import heapq
from typing import List, Tuple


@dataclass(order=True)
class Node:
    """Represents one element in the heap with its source array position."""

    value: int
    array_index: int
    element_index: int


def find_smallest_range(arrays: List[List[int]], verbose: bool = False) -> Tuple[int, int]:
    """
    Find the smallest range [start, end] that includes at least one number
    from each sorted array.

    Algorithm:
    - Step 1: Initialize heap with the first element from every array.
    - Step 2: Track current maximum among heap elements.
    - Step 3: Repeatedly pop minimum and update best range.
    - Step 4: Push next element from the popped element's array.
    - Step 5: Stop when any array gets exhausted.

    Time Complexity: O(nk log k) where k = number of arrays, n = average array size.
    Space Complexity: O(k)
    """
    if not arrays or any(len(arr) == 0 for arr in arrays):
        raise ValueError("All arrays must be non-empty.")

    # Step 1: Initialize heap
    min_heap: List[Node] = []
    current_max = float("-inf")

    for i, arr in enumerate(arrays):
        node = Node(arr[0], i, 0)
        heapq.heappush(min_heap, node)
        current_max = max(current_max, arr[0])

    best_start = min_heap[0].value
    best_end = int(current_max)

    if verbose:
        print("Initial heap built with first element from each array.")
        print(f"Current range: [{best_start}, {best_end}]")

    while True:
        # Current minimum comes from heap root.
        min_node = heapq.heappop(min_heap)
        current_min = min_node.value

        # Update best range if this one is tighter.
        if current_max - current_min < best_end - best_start:
            best_start, best_end = current_min, int(current_max)
            if verbose:
                print(f"Updated best range -> [{best_start}, {best_end}]")

        next_index = min_node.element_index + 1
        source_array = arrays[min_node.array_index]

        # Stop when any array is exhausted.
        if next_index >= len(source_array):
            break

        next_value = source_array[next_index]
        heapq.heappush(
            min_heap,
            Node(next_value, min_node.array_index, next_index),
        )

        # Step 2: Track max value
        if next_value > current_max:
            current_max = next_value

        if verbose:
            print(
                "Popped min:",
                current_min,
                "| pushed next:",
                next_value,
                "| current max:",
                current_max,
            )

    return best_start, best_end
