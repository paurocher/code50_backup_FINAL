#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }



    // print the prefs array. DELETE THIS LATER
    // for (int i = 0; i < voter_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%i: %i\n", i, preferences[i][j]);
    //     }
    // }
    //////////////////////////




    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();


        // print the candidates array. DELETE THIS LATER
        for (int i = 0; i < candidate_count; i++)
        {
            printf("total votes candidate %s %i\n", candidates[i].name, candidates[i].votes);
        }
        //////////////////////////




        // Check if election has been won

        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int i = 0; i < candidate_count; i++)
    {
        // verify name exists
        if (strcmp(name, candidates[i].name) == 0)
        {
            // if name exists, check it is not already in the preferences array
            bool already_in = false;
            for (int j = 0; j < candidate_count; j++)
            {
                if (i + 1 == preferences[voter][j])
                {
                    // as the array is prefilled with 0s I do not want to search for duplicates with 0, this is why I am adding 1 to i
                    //printf("already in\n");
                    already_in = true;
                    return false;
                }
            }
            if (!already_in)
            {
                // adding the candidate ID + 1 so we do not compare with )s in the if statement above
                preferences[voter][rank] = i + 1;
                return true;
            }
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // iterate voters (y axis of prefs)
    for (int voter = 0; voter < voter_count; voter++)
    {
        // iterate choices (x axis of prefs)
        bool counted_vote = false;
        for (int pref_id = 0; pref_id < candidate_count; pref_id++)
        {
            // this var keeps track if the vote has already been counted. If it has, ignore this vote and get to the next one.
            if (!counted_vote)
            {
                int pref = preferences[voter][pref_id] - 1;  // the chosen candidate (starting at 1)
                printf("rank: %i, voter: %i choice: %i\n", pref_id, voter, pref);

                // if candidate not eleiminated increment votes
                if (!candidates[pref].eliminated)
                {
                    candidates[pref].votes++;
                    counted_vote = true;
                }
            }
        }
    }
    printf("\n");
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // figure out if any candidate has more than half the amount of votes
    for (int can = 0; can < candidate_count; can++)
    {
        // if so, print the winner and return true
        if (candidates[can].votes > voter_count / 2)
        {
            printf("%s\n", candidates[can].name);
            return true;
        }
    }
    //else return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int smallest = voter_count;
    for (int can = 0; can < candidate_count; can++)
    {
        if (!candidates[can].eliminated)
        {
            if (candidates[can].votes < smallest)
            {
                smallest = candidates[can].votes;
            }
        }
    }
    return smallest;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Get amount of votes first non disabled has because I really do not get how min would help  me here ...
    // Then I will compare it to the other non disabled candidated.
    int votes = 0;
    for (int can = 0; can < candidate_count; can++)
    {
        if (!candidates[can].eliminated)
        {
            votes = candidates[can].votes;
            break;
        }
    }
    // compare it to the rest of candidates
    for (int can2 = 0; can2 < candidate_count; can2++)
    {
        if (!candidates[can2].eliminated)
        {
            if (candidates[can2].votes != votes)
            {
                return false;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int can = 0; can < candidate_count; can++)
    {
        if (!candidates[can].eliminated)
        {
            if (candidates[can].votes <= min)
            {
                candidates[can].eliminated = true;
            }
        }
    }
    return;
}
