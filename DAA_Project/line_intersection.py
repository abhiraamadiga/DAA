"""Sweep-line based intersection counting between horizontal and vertical segments."""

from bisect import bisect_left, bisect_right, insort
from typing import List, Tuple


START = 0
VERTICAL = 1
END = 2

HorizontalSegment = Tuple[int, int, int]  # (x1, x2, y)
VerticalSegment = Tuple[int, int, int]  # (x, y1, y2)


def count_intersections(
    horizontal_segments: List[HorizontalSegment],
    vertical_segments: List[VerticalSegment],
    verbose: bool = False,
) -> int:
    """
    Count intersections between horizontal and vertical line segments using sweep line.

    Event representation:
    - Horizontal start: (x1, START, y, y)
    - Horizontal end:   (x2, END, y, y)
    - Vertical line:    (x, VERTICAL, y1, y2)

    Ordering START < VERTICAL < END at same x ensures inclusiveness at boundaries.

    Time Complexity: O((H + V) log H) where H = horizontal count, V = vertical count.
    Space Complexity: O(H)
    """
    events: List[Tuple[int, int, int, int]] = []

    for x1, x2, y in horizontal_segments:
        if x1 > x2:
            x1, x2 = x2, x1
        events.append((x1, START, y, y))
        events.append((x2, END, y, y))

    for x, y1, y2 in vertical_segments:
        if y1 > y2:
            y1, y2 = y2, y1
        events.append((x, VERTICAL, y1, y2))

    events.sort()

    active_y: List[int] = []
    intersections = 0

    for event_x, event_type, y1, y2 in events:
        if event_type == START:
            # Activate horizontal line at y.
            insort(active_y, y1)
            if verbose:
                print(f"x={event_x}: START horizontal y={y1}, active={active_y}")
        elif event_type == END:
            # Deactivate one occurrence of horizontal line at y.
            idx = bisect_left(active_y, y1)
            if idx < len(active_y) and active_y[idx] == y1:
                active_y.pop(idx)
            if verbose:
                print(f"x={event_x}: END horizontal y={y1}, active={active_y}")
        else:
            # Count active horizontals whose y is within [y1, y2].
            left = bisect_left(active_y, y1)
            right = bisect_right(active_y, y2)
            count_here = right - left
            intersections += count_here
            if verbose:
                print(
                    f"x={event_x}: VERTICAL y=[{y1}, {y2}],",
                    f"hits={count_here}, total={intersections}",
                )

    return intersections
