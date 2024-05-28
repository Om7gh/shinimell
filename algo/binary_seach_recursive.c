#include <stdio.h>


int binary_seach_recursive(int *arr, int low, int height, int n)
{
        if (low <= height)
        {
                int middl = low + (height - low) / 2;
                if (arr[middl] == n)
                        return (middl);
                else if (arr[middl] < n)
                        return (binary_seach_recursive(arr, middl + 1, height, n));
                else
                        return (binary_seach_recursive(arr, low, middl - 1, n));
        }
        return (-1);
}

int main()
{
        int arr[] = {9,5,10,44,16,13,79,98};

        int size = sizeof(arr) / sizeof(int);

        printf("%d\n", binary_seach_recursive(arr, 0, size - 1, 5));
}
