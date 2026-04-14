"""Utility helpers for input parsing and sample test data."""

from typing import List, Tuple

HorizontalSegment = Tuple[int, int, int]  # (x1, x2, y)
VerticalSegment = Tuple[int, int, int]  # (x, y1, y2)


def parse_int_list(prompt: str) -> List[int]:
    """Read a space-separated list of integers from user input."""
    values = input(prompt).strip().split()
    return [int(v) for v in values]


def input_k_sorted_arrays() -> List[List[int]]:
    """Take k sorted arrays as input from user."""
    k = int(input("Enter number of arrays (k): ").strip())
    arrays: List[List[int]] = []

    for i in range(k):
        arr = parse_int_list(
            f"Enter sorted elements of array {i + 1} (space-separated): "
        )
        arrays.append(arr)

    return arrays


def input_line_segments() -> Tuple[List[HorizontalSegment], List[VerticalSegment]]:
    """Take horizontal and vertical segments as input from user."""
    h = int(input("Enter number of horizontal segments: ").strip())
    horizontal_segments: List[HorizontalSegment] = []

    print("Enter each horizontal segment as: x1 x2 y")
    for i in range(h):
        x1, x2, y = parse_int_list(f"H{i + 1}: ")
        horizontal_segments.append((x1, x2, y))

    v = int(input("Enter number of vertical segments: ").strip())
    vertical_segments: List[VerticalSegment] = []

    print("Enter each vertical segment as: x y1 y2")
    for i in range(v):
        x, y1, y2 = parse_int_list(f"V{i + 1}: ")
        vertical_segments.append((x, y1, y2))

    return horizontal_segments, vertical_segments


def sample_data_smallest_range() -> List[List[int]]:
    """Sample test case for smallest range problem."""
    return [
        [4, 7, 9, 12, 15],
        [0, 8, 10, 14, 20],
        [6, 12, 16, 30, 50],
    ]


def sample_data_line_intersections() -> Tuple[List[HorizontalSegment], List[VerticalSegment]]:
    """Sample test case for line segment intersection problem."""
    horizontal = [
        (1, 5, 2),
        (2, 7, 4),
        (6, 9, 1),
    ]
    vertical = [
        (3, 1, 5),
        (6, 0, 4),
        (8, 1, 3),
    ]
    return horizontal, vertical


def sample_data_msis() -> List[int]:
    """Sample test case for MSIS problem."""
    return [1, 101, 2, 3, 100, 4, 5]
