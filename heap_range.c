#include "heap_range.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int array_index;
    int element_index;
} HeapNode;

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(HeapNode *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].value <= heap[index].value) {
            break;
        }
        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static void heapify_down(HeapNode *heap, int size, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }
        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }

        swap_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void heap_push(HeapNode *heap, int *size, HeapNode value) {
    heap[*size] = value;
    heapify_up(heap, *size);
    (*size)++;
}

static HeapNode heap_pop(HeapNode *heap, int *size) {
    HeapNode root = heap[0];
    (*size)--;
    heap[0] = heap[*size];
    heapify_down(heap, *size, 0);
    return root;
}

int find_smallest_range(
    const IntArray *arrays,
    int k,
    int verbose,
    int *out_start,
    int *out_end
) {
    int i;
    int heap_size = 0;
    int current_max = INT_MIN;
    int best_start;
    int best_end;
    HeapNode *heap;

    if (arrays == NULL || k <= 0 || out_start == NULL || out_end == NULL) {
        return 0;
    }

    for (i = 0; i < k; i++) {
        if (arrays[i].size <= 0 || arrays[i].data == NULL) {
            return 0;
        }
    }

    heap = (HeapNode *)malloc((size_t)k * sizeof(HeapNode));
    if (heap == NULL) {
        return 0;
    }

    for (i = 0; i < k; i++) {
        HeapNode node;
        node.value = arrays[i].data[0];
        node.array_index = i;
        node.element_index = 0;
        heap_push(heap, &heap_size, node);

        if (node.value > current_max) {
            current_max = node.value;
        }
    }

    best_start = heap[0].value;
    best_end = current_max;

    if (verbose) {
        printf("Initial heap built with first element from each array.\n");
        printf("Current range: [%d, %d]\n", best_start, best_end);
    }

    while (heap_size == k) {
        HeapNode min_node = heap_pop(heap, &heap_size);
        int current_min = min_node.value;
        int next_index = min_node.element_index + 1;
        int array_index = min_node.array_index;

        if ((current_max - current_min) < (best_end - best_start)) {
            best_start = current_min;
            best_end = current_max;
            if (verbose) {
                printf("Updated best range -> [%d, %d]\n", best_start, best_end);
            }
        }

        if (next_index >= arrays[array_index].size) {
            break;
        }

        {
            int next_value = arrays[array_index].data[next_index];
            HeapNode next_node;
            next_node.value = next_value;
            next_node.array_index = array_index;
            next_node.element_index = next_index;
            heap_push(heap, &heap_size, next_node);

            if (next_value > current_max) {
                current_max = next_value;
            }

            if (verbose) {
                printf(
                    "Popped min: %d | pushed next: %d | current max: %d\n",
                    current_min,
                    next_value,
                    current_max
                );
            }
        }
    }

    free(heap);
    *out_start = best_start;
    *out_end = best_end;
    return 1;
}