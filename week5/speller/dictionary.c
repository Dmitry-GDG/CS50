// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Number of words in the dictionary
unsigned int Nbr_words;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *tmp;
    if (!table[hash(word)])
    {
        return false;
    }
    tmp = table[hash(word)];
    if (strcasecmp(word, tmp->word) == 0)
    {
        return true;
    }
    if (tmp->next != NULL)
    {
        while (tmp->next != NULL)
        {
            if (strcasecmp(word, tmp->next->word) == 0)
            {
                return true;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int outp = 0;
    if ((word[0] >= 'A') && (word[0] <= 'Z'))
    {
        outp = word[0] - 'A';
    }
    else if ((word[0] >= 'a') && (word[0] <= 'z'))
    {
        outp = word[0] - 'a';
    }
    return (outp);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    char str_word[LENGTH];
    unsigned int position; // position in the hash table
    Nbr_words = 0;
    while (fscanf(inptr, "%s", str_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fprintf(stderr, "Not enough memory\n");
            fclose(inptr);
            return false;
        }
        else
        {
            strcpy(n->word, str_word);
            position = hash(str_word);
            n->next = table[position];
            table[position] = n;
            Nbr_words++;
        }
    }
    // Close infile
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return (Nbr_words);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    unsigned int i;
    node *tmp;

    for (i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            while (table[i]->next != NULL)
            {
                tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
            free(table[i]);
        }
    }
    return true;
}

// call it:
// make
// valgrind ./speller texts/cat.txt
// ./speller texts/lalaland.txt
// ./speller dictionaries/small texts/lalaland.txt
// ./speller texts/lalaland.txt > student.txt
// ~cs50/2019/fall/pset5/speller texts/lalaland.txt > staff.txt
// diff -y student.txt staff.txt