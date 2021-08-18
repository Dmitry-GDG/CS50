#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long    nbr;
    int     qty_digits;
    long    tmp;
    int     odd;
    int     sum;
    int     app;

    do
    {
        nbr = get_long("Number: ");
    }
    while (nbr <= 0);
    qty_digits = 0;
    tmp = nbr;
    odd = 0;
    sum = 0;
    while (tmp > 0)
    {
        qty_digits++;
        app = tmp % 10;
        if (odd == 1)
        {
            odd = 0;
            if (app < 5)
            {
                sum += 2 * app;
            }
            else
            {
                sum = sum + 1 + (app - 5) * 2;
            }
        }
        else
        {
            sum += app;
            odd = 1;
        }
        tmp /= 10;
    }
    if (sum % 10 == 0 && qty_digits == 15 && ((nbr >= 340000000000000 && nbr < 349999999999999) \
            || (nbr >= 370000000000000 && nbr < 379999999999999)))
    {
        printf("AMEX\n");
    }
    else if (sum % 10 == 0 && qty_digits == 16 && (nbr >= 5100000000000000 && nbr < 5599999999999999))
    {
        printf("MASTERCARD\n");
    }
    else if (sum % 10 == 0 && (qty_digits == 13 || qty_digits == 16) && ((nbr >= 400000000000000 && nbr < 4999999999999999) \
             || (nbr >= 400000000000 && nbr < 4999999999999)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return (0);
}
