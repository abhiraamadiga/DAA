#include "line_intersection.h"

#include <stdio.h>
#include <stdlib.h>

#define START 0
#define VERTICAL 1
#define END 2

typedef struct {
    int x;
    int type;
    int y1;
    int y2;
} Event;

static int compare_events(const void *a, const void *b) {
    const Event *ea = (const Event *)a;
    const Event *eb = (const Event *)b;

    if (ea->x != eb->x) {
        return (ea->x < eb->x) ? -1 : 1;
    }
    if (ea->type != eb->type) {
        return (ea->type < eb->type) ? -1 : 1;
    }
    return 0;
}

static int lower_bound(const int *arr, int n, int value) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

static int upper_bound(const int *arr, int n, int value) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

static void insert_sorted(int *arr, int *n, int value) {
    int i;
    int pos = lower_bound(arr, *n, value);
    for (i = *n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    (*n)++;
}

static void remove_one(int *arr, int *n, int value) {
    int i;
    int pos = lower_bound(arr, *n, value);
    if (pos >= *n || arr[pos] != value) {
        return;
    }
    for (i = pos; i < (*n - 1); i++) {
        arr[i] = arr[i + 1];
    }
    (*n)--;
}

int count_intersections(
    const HorizontalSegment *horizontal_segments,
    int h_count,
    const VerticalSegment *vertical_segments,
    int v_count,
    int verbose
) {
    int i;
    int event_count;
    int event_index;
    int intersections = 0;
    Event *events;
    int *active_y;
    int active_count = 0;

    if ((h_count > 0 && horizontal_segments == NULL) ||
        (v_count > 0 && vertical_segments == NULL)) {
        return 0;
    }

    event_count = 2 * h_count + v_count;
    events = (Event *)malloc((size_t)event_count * sizeof(Event));
    active_y = (int *)malloc((size_t)(h_count > 0 ? h_count : 1) * sizeof(int));
    if (events == NULL || active_y == NULL) {
        free(events);
        free(active_y);
        return 0;
    }

    event_index = 0;
    for (i = 0; i < h_count; i++) {
        int x1 = horizontal_segments[i].x1;
        int x2 = horizontal_segments[i].x2;
        int y = horizontal_segments[i].y;
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        events[event_index++] = (Event){x1, START, y, y};
        events[event_index++] = (Event){x2, END, y, y};
    }

    for (i = 0; i < v_count; i++) {
        int y1 = vertical_segments[i].y1;
        int y2 = vertical_segments[i].y2;
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        events[event_index++] = (Event){vertical_segments[i].x, VERTICAL, y1, y2};
    }

    qsort(events, (size_t)event_count, sizeof(Event), compare_events);

    for (i = 0; i < event_count; i++) {
        Event e = events[i];
        if (e.type == START) {
            insert_sorted(active_y, &active_count, e.y1);
            if (verbose) {
                printf("x=%d: START horizontal y=%d\n", e.x, e.y1);
            }
        } else if (e.type == END) {
            remove_one(active_y, &active_count, e.y1);
            if (verbose) {
                printf("x=%d: END horizontal y=%d\n", e.x, e.y1);
            }
        } else {
            int left = lower_bound(active_y, active_count, e.y1);
            int right = upper_bound(active_y, active_count, e.y2);
            int count_here = right - left;
            intersections += count_here;
            if (verbose) {
                printf(
                    "x=%d: VERTICAL y=[%d, %d], hits=%d, total=%d\n",
                    e.x,
                    e.y1,
                    e.y2,
                    count_here,
                    intersections
                );
            }
        }
    }

    free(events);
    free(active_y);
    return intersections;
}