#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    int j;

    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    i = 0;
    while (argv[1][i])
    {
        if (argv[1][i] < 'A' || (argv[1][i] > 'Z' && argv[1][i] < 'a') || argv[1][i] > 'z')
        {
            printf("The key is containing not an alphabetic character\n");
            return (1);
        }
        else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] -= 32;
        }
        j = i + 1;
        while (argv[1][j])
        {
            if (argv[1][i] == argv[1][j] || argv[1][i] == (argv[1][j] - 32))
            {
                printf("The key not containing each letter exactly once\n");
                return (1);
            }
            j++;
        }
        i++;
    }
    if (i != 26)
    {
        printf("The key must contain 26 characters.\n");
        return (1);
    }
//    printf("%s\n", argv[1]);
    string inp = get_string("plaintext: ");
    printf("ciphertext: ");
    i = 0;
    while (inp[i])
    {
        if (((inp[i] <= 'z') && (inp[i] >= 'a')) || ((inp[i] <= 'Z') && (inp[i] >= 'A')))
        {
            if ((inp[i] <= 'Z') && (inp[i] >= 'A'))
            {
                printf("%c", argv[1][inp[i] - 'A']);
            }
            else if ((inp[i] <= 'z') && (inp[i] >= 'a'))
            {
                printf("%c", (char)(argv[1][inp[i] - 'a'] + 32));
            }
        }
        else
        {
            printf("%c", inp[i]);
        }
        i++;
    }
    printf("\n");
    return (0);
}
