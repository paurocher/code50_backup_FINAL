// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word); // Get starting point to search from
    node *cursor = table[hash_value];

    // iterate through list until word is found or until end of lit (nex=NULL)
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // from:
    // https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/HashFuncExamp.html#a-simple-hash-function-for-strings
    unsigned int total = 0; // Total of all summed up letters of the word
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

int counter = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open file\n");
        return false;
    }

    // read lines
    // var holding the word to hash with a max length defined in dictionary.h (45)
    char word[LENGTH + 1];
    // iterate through all words in dict and hash 'em
    while (fscanf(source, "%s", word) != EOF) // get single word untiil reaching EndOfFile
    {
        // allocate memory for new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate memory for new node.\n");
            return false;
        }
        // copy the string being processed to the new node
        strcpy(n->word, word);
        // hash the word
        //    get bubket (hash) of the word
        int hash_number = hash(word);
        //    set next val to root value (in the table array)
        n->next = table[hash_number];
        //    make the root value in the table array point to this node
        table[hash_number] = n;

        counter++;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Do this for the whole length of table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL) // free all linked nodes by creating a tmp node, assigning it to the cursor node value, setting cursoer to the next node it points to, clearing the temp node again adn again until finding the value of NULL on a cursor which marks the end of the list.
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (cursor == NULL &&
            i == N - 1) // end of list because of NULL and N-1 (which is the last entry in the list)
        {
            return true;
        }
    }
    return false;
}
