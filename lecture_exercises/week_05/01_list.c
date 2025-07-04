#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL; // declare the list var name

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node)); // allocate a pointer called n which is the returned value of malloc to the size of what the size of node is. So here we are creating a space anywhere in the memory for a 'node'.
        if (n == NULL)
        {
            // free memory thus far
            return 1;
        }
        n->number = number; // go into n, follow that pointer to the 'number' field and set it equal to the actual number

        // before we point the list to the new node, first grab the newly created node, and set its 'next' pointer to list
        n->next = list;

        list = n; // now we can tell 'list' to point to n and thus the chain starts on 'list', then follows each 'n' created in the loop that chain each other as well
    }

    // Print the whole list
    node *ptr = list; // we start by creating a pointer which is a node set to list. So this pointer points at whatever 'list' is pointing first
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);

        ptr = ptr->next; // set pointer to the next in the chain
    }

    // This will print 4, 3, 2, 1 (depending on the numbers given as args). The args in reverse because we have been prepending on list
}
