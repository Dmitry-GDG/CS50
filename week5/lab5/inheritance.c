// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <string.h>
//#include <math.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    int n_parents = 2; // qty parents
    int n_genes = 2; // qty genders
    int cur_parent = 0;  // current parent

    // TODO: Allocate memory for new person
    person *current = malloc(sizeof(person));
    if (current == NULL)
    {
        return NULL;
    }

    // Generation with parent data
    if (generations > 1) // Need to dig deeper
    {
        int gen_num; // Randomly assigned parent (0 or 1)

        // Create parents, choose one gens from each their parent
        while (cur_parent < n_parents)
        {
            // TODO: Recursively create blood type histories for parents
            current->parents[cur_parent] = create_family(generations - 1);
            // TODO: Randomly assign child alleles based on parents
            gen_num = rand() % n_genes;
            current->alleles[cur_parent] = current->parents[cur_parent]->alleles[gen_num];
            ++cur_parent;
        }
    }
    // Generation without parent data
    else if (generations == 1)
    {
        // Simulate genes for oldest geneneration
        while (cur_parent < n_parents)
        {
            // TODO: Set parent pointers to NULL
            current->parents[cur_parent] = NULL;

            // TODO: Randomly assign alleles
            current->alleles[cur_parent] = random_allele();
            ++cur_parent;
        }
    }
    else
    {
        printf("Generations < 1\n");
    }
    // TODO: Return newly created person
    return current;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    // TODO: Free parents
    // TODO: Free child
    if (p) // p is not NULL
    {
        free_family(p->parents[0]);
        free_family(p->parents[1]);
        free(p);
    }
    return;
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

/* call it:
* make inheritance && ./inheritance */