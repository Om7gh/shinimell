
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

int findSmallest(int arr[], int size) {
    int smallest = arr[0];
    int smallest_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
            smallest_index = i;
        }
    }
    return smallest_index;
}

#define SIZE 50000
void selectionSort(int arr[], int size) {
    int newArr[size];
    for (int i = 0; i < size; i++) {
        int smallest = findSmallest(arr, size);
        newArr[i] = arr[smallest];
        arr[smallest] = INT_MAX;
    }
    for(int i = 0; i < size; i++)
        arr[i] = newArr[i];
}

int main() {
     int arr[SIZE];
    
    srand(time(NULL));
    
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 100000; 
    int size = (sizeof(arr) / sizeof(int));
    selectionSort(arr, size);
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

