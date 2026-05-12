// Count of Smaller Numbers After Self using Merge Sort
// LeetCode Style C Code

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Pair;

void merge(Pair* arr, int left, int mid, int right, int* count) {
    int n = right - left + 1;
    Pair* temp = (Pair*)malloc(n * sizeof(Pair));

    int i = left;
    int j = mid + 1;
    int k = 0;
    int rightCount = 0;

    while (i <= mid && j <= right) {
        if (arr[j].val < arr[i].val) {
            temp[k++] = arr[j++];
            rightCount++;
        } else {
            count[arr[i].idx] += rightCount;
            temp[k++] = arr[i++];
        }
    }

    while (i <= mid) {
        count[arr[i].idx] += rightCount;
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }

    free(temp);
}

void mergeSort(Pair* arr, int left, int right, int* count) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid, count);
    mergeSort(arr, mid + 1, right, count);

    merge(arr, left, mid, right, count);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int* count = (int*)calloc(numsSize, sizeof(int));
    Pair* arr = (Pair*)malloc(numsSize * sizeof(Pair));

    for (int i = 0; i < numsSize; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }

    mergeSort(arr, 0, numsSize - 1, count);

    free(arr);
    return count;
}

// Example usage
int main() {
    int nums[] = {5, 2, 6, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* result = countSmaller(nums, n, &returnSize);

    printf("Output: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}