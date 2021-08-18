#include <stdio.h>
#include <cs50.h>

int	main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    } while (n < 1 || n > 8);
//  printf ("Stored: %i\n", n);
    for (int i = 1; i <= n; i++)
    {
        int j = n - i;
        while (j > 0)
        {
            printf(" ");
            j--;
        }
        j = i;
        while (j > 0)
        {
            printf("#");
            j--;
        }
        printf ("\n");
    }
    return (0);
}