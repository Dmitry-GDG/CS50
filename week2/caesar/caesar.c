#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;

    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    i = 0;
    while (argv[1][i] != '\0')
    {
        if (argv[1][i] > '9' || argv[1][i] < '0')
        {
            printf("Usage: ./caesar key\n");
            return (1);
        }
        else
        {
            i++;
        }
    }
    int key = atoi(argv[1]);
    if (key >= 26)
    {
        while (key >= 26)
        {
            key -= 26;
        }
    }
//  printf("%d\n", key);
    string inp = get_string("plaintext: ");
    printf("ciphertext: ");
    i = 0;
    while (inp[i])
    {
        if (((inp[i] <= 'z') && (inp[i] >= 'a')) || ((inp[i] <= 'Z') && (inp[i] >= 'A')))
        {
            if (((inp[i] + key) <= 'z') && ((inp[i] + key) >= 'a'))
            {
                printf("%c", (char)(inp[i] + key));
            }
            else if ((inp[i] + key) > 'z')
            {
                printf("%c", (char)(inp[i] + key - 26));
            }
            else if (((inp[i] + key) <= 'Z') && ((inp[i] + key) >= 'A'))
            {
                printf("%c", (char)(inp[i] + key));
            }
            else if ((inp[i] + key) > 'Z')
            {
                printf("%c", (char)(inp[i] + key - 26));
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
