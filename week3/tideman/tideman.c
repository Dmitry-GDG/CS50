#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
        else
        {
            i++;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int i;
    int j;

    i = 0;
    while (i < candidate_count - 1)
    {
        j = i + 1;
        while (j < candidate_count)
        {
            preferences[ranks[i]][ranks[j]]++;
            j++;
        }
        i++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
//    pair pairs[MAX * (MAX - 1) / 2];
//    int pair_count;
//    typedef struct
//    {
//       int winner;
//       int loser;
//    }
//    pair;
    int i;
    int j;

    i = 0;
    while (i < candidate_count)
    {
        j = i + 1;
        while (j < candidate_count)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            j++;
        }
        i++;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair    tmp;
    int     i;

    i = 0;
    while (i < pair_count - 2)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            tmp.winner = pairs[i].winner;
            tmp.loser = pairs[i].loser;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].winner = tmp.winner;
            pairs[i + 1].loser = tmp.loser;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    return;
}

bool if_cycle(int start, int finish)
{
    int i = 0;
    if (locked[finish][start])
    {
        return true;
    }
    // Reduce "start to finish"
    // by recursive finding "i to finish"
    while (i < candidate_count)
    {
        if (locked[i][start])
        {
            if (if_cycle(i, finish))
            {
                return true;
            }
        }
        i++;
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i = 0;
    while (i < pair_count)
    {
        if (!if_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        i++;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int i;
    int j;
    int pairs_tied;

    j = 0;
    while (j < candidate_count)
    {
        i = 0;
        pairs_tied = 0;
        while (i < candidate_count)
        {
            if (locked[i][j] == true)
            {
                pairs_tied++;
            }
            i++;
        }
        if (pairs_tied == 0)
        {
            printf("%s\n", candidates[j]);
        }
        j++;
    }
    return;
}
