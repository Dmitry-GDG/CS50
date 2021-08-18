#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float   dollars;
    int     outp;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    int cents = round(dollars * 100);
    outp = 0;
    while (cents - 25 * outp >= 25)
    {
        outp ++;
    }
    cents -= 25 * outp;
    if (cents >= 20)
    {
        outp += 2;
        cents -= 20;
    }
    else if (cents >= 10)
    {
        outp += 1;
        cents -= 10;
    }
    if (cents >= 5)
    {
        outp += 1;
        cents -= 5;
    }
    outp += cents;
    printf("%i\n", outp);
    return (0);
}
