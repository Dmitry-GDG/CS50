#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int qty_letters = 0;
    int qty_words = 0;
    int qty_sentences = 0;
    int i;
    string inp;
    int outp;

    // Getting text
    do
    {
        inp = get_string("Text: ");
    }
    while (!inp);
    // Calculating quantity of letters
    i = 0;
    while (inp[i])
    {
        if (((inp[i] >= 'a' &&  inp[i] <= 'z')) || ((inp[i] >= 'A' &&  inp[i] <= 'Z')))
        {
            qty_letters++;
        }
        i++;
    }
//    printf("qty_letters: %d\n", qty_letters);
    // Calculating quantity of words and setences
    i = 0;
    while (inp[i])
    {
        while ((inp[i] >= '\t' && inp[i] <= '\r') || inp[i] == 32)
        {
            i++;
        }
        if (inp[i])
        {
            qty_words++;
        }
        while (inp[i] != '\n' && inp[i] != '\t' && inp[i] != '\v' && inp[i] != '\r' && inp[i] != '\f' && inp[i] != 32 && inp[i] != 0 \
               && inp[i] != '.' && inp[i] != '!' && inp[i] != '?')
        {
            i++;
        }
        if (inp[i] == '.' || inp[i] == '!' || inp[i] == '?')
        {
            qty_sentences++;
            i++;
        }
    }
//    printf("qty_words: %d\n", qty_words);
//    printf("qty_sentences: %d\n", qty_sentences);
    //Calculating grading
    outp = round(0.0588 * (qty_letters * 100 / (float) qty_words) - 0.296 * (qty_sentences * 100 / (float) qty_words) - 15.8);
    if (outp < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (outp > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", outp);
    }
    return (0);
}
