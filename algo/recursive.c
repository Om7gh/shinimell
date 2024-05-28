#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500

int calc_sum(int *arr, int size)
{
        int sum;
        if (size == 0)
                return (0);
        if (size == 1)
                return (arr[0]);
        else
                sum = arr[0] + (calc_sum(arr + 1, size - 1));
        return (sum);
}

int main()
{
        int *arr = malloc(sizeof(int) * SIZE);

        srand(time(NULL));
        for (int i = 0; i < SIZE; i++)
                arr[i] = rand() % 1000;
        printf("sum is %d\n", calc_sum(arr, SIZE));
}
