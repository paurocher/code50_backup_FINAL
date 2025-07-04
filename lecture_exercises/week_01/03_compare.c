#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int first = get_int("First number: ");
    int second = get_int("Second number: ");

    if (first > second)
    {
        printf("%i is larger than %i", first, second);
    }
    else if (first < second)
    {
        printf("%i is smaller than %i", first, second);
    }
    else
    {
        printf("numbers are equal\n");
    }
}
