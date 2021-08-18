#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size1;
    int size2;
// size1 must be not less then 9
    do
    {
        size1 = get_int("Start size: ");
    }
    while (size1 < 9);
// size2 must be not less then size1
    do
    {
        size2 = get_int("End size: ");
    }
    while (size2 < size1);
    int year = 0;
    while (size1 < size2)
    {
        int gain = size1 / 3;
        int lose = size1 / 4;
        size1 += gain - lose;
        year++;
    }
    printf("Years: %d\n", year);
    return (0);
}
