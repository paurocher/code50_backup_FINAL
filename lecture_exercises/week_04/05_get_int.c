#include <stdio.h>


// We are creating there a replica of the cs50 library 'getint' (minus error handling).
int main(void)
{
    int n; // create variable
    printf("n: "); // prompt user
    scanf("%i", &n); // scanf grabs the user input and asigns it to a variable pointer
    printf("n: %i\n", n); // here we verify the var value has been set.
}


    // Getting strings: well this is actually very complicated, so we will use cs50 library fr strings (and for any other type of var if we want :) )
