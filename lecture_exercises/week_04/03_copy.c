#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    char *s = get_string("s: ");
    if (t == NULL) // this is here to break the program in case the computer runs out of memory
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1); // This will only copy the mem location, so not a real copy of the string!
    if (t == NULL)
    {
        return 1;
    }

    // this is an arcane  way to copy strings!
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    // a more modern way to opy string would be: strcpy(t, s)

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("%s\n", s);
    printf("%s\n", t);

    free(t); //good practice: free up the memory you allocated earlier
    return 0;
}
