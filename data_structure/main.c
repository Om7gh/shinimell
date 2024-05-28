#include <libc.h>

int     get_number(int **matrice, int x, int y, int number)
{
        int     i;
        int     j;

        i = 0;
        while (i < x - 1)
        {
                j = 0;
                while (j < y - 1)
                {
                        if (matrice[i][j] == number)
                                return (printf("number is found %d\n", matrice[i][j]));
                        j++;
                }
                i++;
        }
        return (printf("number not found"));
}

int main(int ac, char **av)
{
        int     matrice[5][5] = {{1,2,3,4,5}, {6,5,4,9,10}, {11,12,13,15,16}, {17,18,19,20,21}, {22,23,24,25,26}};
        int get = get_number((int **)matrice, 5, 5, 23);
        if (get)
                printf("%d\n", get);
        return (EXIT_SUCCESS);
}
