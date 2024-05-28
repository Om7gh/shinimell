#include <stdio.h>
#include <string.h>


int binary_search(int tab[], int item, int len)
{
        int low = 0;
        int height = len - 1;
        int middl;
        int guess;

        while (low <= height)
        {
                middl = (low + height) / 2;
                guess = tab[middl];
                if (guess == item)
                        return (middl);
                if (guess > item)
                        height = middl - 1;
                else if (guess < item)
                        low = middl + 1;
        }
        return (-1);
}

int main()
{
        int     tab[] = {1,2,3,4,5,6,7,8,9};
        int size = 9;
        printf("%d\n", binary_search(tab, 9, size));
}
