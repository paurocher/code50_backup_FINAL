Data structures

Abstract Data Types

# Queues
FIFO: characteristic of queues: First In First Out
enqueue / dequeue: prepare the list, use the list
SO it is basically an array.
We can define one like so:
'''
const int CAPACITY = 50;
typedef struct
{
    person people[CAPACITY];
    int size;
}queue;
'''
Here we defined a queu that stores 50 people. "people" is the type we defined in a previous week.
IN queues we need to keep track of the size. In this exampple we can put a max of 50 but in size we keep track of how maney there actually are in reality, that we have inserted or are left  inside.


# Stacks
LIFO: Last In First Out (the last information that was inserted will be the first accessed)
'push' and 'pop' are the analogous functions of enqueuing snd dequeuing for stacks.
We implement them the same as queues:
'''
typedef struct
{
    person people[CAPACITY];
    int size;
}stack;
'''


The limitation of arrays or malloc is that they are a definite size of memory.
With pointers and struct (using the '.' to reference internal data of the struct (name, phone_number, ...) and the '*' that means different things in different contexts (declare or derefference(= go there) a pointer) and the '->' which is a combination of '*.'  that points from one place to another).

# Linked lists
with pointers we can make a list grow without worrying about it being contiguous in memory. This circumvents the complex problem of having to make a new array of the new bigger size. The trade-off is that pointer take space in memory.
THese combos of value and pointer are called nodes.
To define a node:
'''
typdef struct node
{
    int number;
    struct node *next;  // This is what we use to link nodes together. It is a pointer to a place in memory where another node exists
} node
'''
New thing here is that we have name the structure at the top (not ony at the bottom as previously). THis allows us to reference the struct inside itself).
This struct holds a value of int type and a pointer to the next node.
In 01_list.c there is an implementation of a linked list.
Prepending to the list as we do in 01_list.c is very fast (O(1)), but searching gets slower as the list grows (O(n)).
Binary search is not possible on lists as they are not a consecutive array of memory chunks, its chunks can be anywhere in the memory.
At 1h10m he tal about 2 cases:
    - appending to a list (add at the end)
    - insert in the list in a sorted fashion


# Binary Trees (1h16m)
```
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;
```
They are (Olog(n)) to search.
Have all upsides of array becauso of binary search, and all up sides and dynamism of linked lists because it can grow or shrink and does not need to be contiguous.
Search is performed recursively.


# Dictionaries (1h30)
Synonim of dictionnary is "hash table".
hashing: takes any number of inputs and maps them to a finite number of outputs. Like sorting a whole deck of cards into 4 colors (hearts, diamonds, ...).
hash table: we can describe it as a combination of arrays and linked lists.
We define them like so:
'''
typedef struct node
{
    char *name;
    char *number;
    struct *node next;
} node;
'''
So this is a new node like before, heolding as many vars as we want and a pointer to the next node if it happens to be a next node, thus this becomes a linked list.
Meanwhile, we have a hash table which is in fact an array holding pointer to nodes:
'''
node *table[26];
'''
Simplest implementation of hash table that looks for the first letter of a given word:
'''
#include <ctype.h>

unsigned int hash(const *char word); // here we have added 'const' which is like the underscore before a var name in python: just letting the compler know that the programmer is not allowed to change this var.
// unsigned forces this function to return only positive numbers starting with 0.
{
    return toupper(word[0]) - 'A';
}
'''
We pass in the first capitalized letter of 'word', substract 'A' from it so it gives us a number between 0 and 25. This number is the entry we want to inspect from a hash table of size 26 we can defin previously


# Tries (1h51)
It is a tree of arrays.
In a try, every node is an array and every array is a letter of the alphabet.

'''
typedef struct node
{
    struct node *children[26];
    int number;
} node;
'''
The way to make the search stop because we have reached the end of a name is by finding a non 'NULL' vlue in the var 'number'.
It takes a huge amount of space but gives constant time fr searching.
