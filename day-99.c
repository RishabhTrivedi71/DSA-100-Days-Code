#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    int speed;
} Car;

// Comparator for sorting by position in descending order
int compare(const void *a, const void *b) {
    Car *c1 = (Car *)a;
    Car *c2 = (Car *)b;
    return c2->position - c1->position;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    if (positionSize == 0)
        return 0;

    Car cars[positionSize];

    // Store cars data
    for (int i = 0; i < positionSize; i++) {
        cars[i].position = position[i];
        cars[i].speed = speed[i];
    }

    // Sort cars by position descending
    qsort(cars, positionSize, sizeof(Car), compare);

    int fleets = 0;
    double maxTime = 0.0;

    // Traverse from nearest car to target
    for (int i = 0; i < positionSize; i++) {
        double time = (double)(target - cars[i].position) / cars[i].speed;

        // New fleet formed
        if (time > maxTime) {
            fleets++;
            maxTime = time;
        }
    }

    return fleets;
}

// Example usage
int main() {
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};

    int n = sizeof(position) / sizeof(position[0]);

    int result = carFleet(target, position, n, speed, n);

    printf("Number of Car Fleets: %d\n", result);

    return 0;
}