#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

// Compare intervals by start time
int compareIntervals(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;
    return i1->start - i2->start;
}

// Min Heap functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int heap[], int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap[parent] <= heap[index])
            break;

        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

void heapifyDown(int heap[], int size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;

        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

void push(int heap[], int *size, int value) {
    heap[*size] = value;
    (*size)++;
    heapifyUp(heap, (*size) - 1);
}

int popMin(int heap[], int *size) {
    int minVal = heap[0];

    heap[0] = heap[*size - 1];
    (*size)--;

    heapifyDown(heap, *size, 0);

    return minVal;
}

int top(int heap[]) {
    return heap[0];
}

// Main function
int minMeetingRooms(Interval intervals[], int n) {
    if (n == 0)
        return 0;

    qsort(intervals, n, sizeof(Interval), compareIntervals);

    int *heap = (int *)malloc(sizeof(int) * n);
    int heapSize = 0;

    // Add first meeting end time
    push(heap, &heapSize, intervals[0].end);

    for (int i = 1; i < n; i++) {

        // Reuse room if possible
        if (intervals[i].start >= top(heap)) {
            popMin(heap, &heapSize);
        }

        // Add current meeting end time
        push(heap, &heapSize, intervals[i].end);
    }

    int result = heapSize;
    free(heap);

    return result;
}

// Example usage
int main() {
    Interval intervals[] = {
        {0, 30},
        {5, 10},
        {15, 20}
    };

    int n = sizeof(intervals) / sizeof(intervals[0]);

    printf("Minimum rooms required: %d\n",
           minMeetingRooms(intervals, n));

    return 0;
}