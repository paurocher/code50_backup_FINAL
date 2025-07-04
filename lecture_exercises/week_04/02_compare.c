#include <cs50.h>
#include <stdio.h>

int main (void)
{
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    printf("%s\n", s);
    printf("%s\n", t);

    printf("%p\n", s); //no need for an `&` as s is already an address
    printf("%p\n", t);
}
