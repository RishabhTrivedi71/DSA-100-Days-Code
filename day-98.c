#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

// Comparator function for sorting
int compare(const void *a, const void *b) {
    Interval *x = (Interval *)a;
    Interval *y = (Interval *)b;
    
    return x->start - y->start;
}

void mergeIntervals(Interval arr[], int n) {
    if (n <= 0)
        return;

    // Sort intervals by start time
    qsort(arr, n, sizeof(Interval), compare);

    Interval result[n];
    int index = 0;

    // First interval
    result[index] = arr[0];

    for (int i = 1; i < n; i++) {
        // Overlapping interval
        if (arr[i].start <= result[index].end) {
            // Merge intervals
            if (arr[i].end > result[index].end)
                result[index].end = arr[i].end;
        } else {
            // Non-overlapping interval
            index++;
            result[index] = arr[i];
        }
    }

    // Print merged intervals
    printf("Merged Intervals:\n");
    for (int i = 0; i <= index; i++) {
        printf("[%d, %d] ", result[i].start, result[i].end);
    }
}

int main() {
    Interval arr[] = {
        {1, 3},
        {2, 6},
        {8, 10},
        {15, 18}
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    mergeIntervals(arr, n);

    return 0;
}