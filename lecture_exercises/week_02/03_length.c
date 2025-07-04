#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Name: ");

    int length = 0;
    while (name[length] != '\0')
    {
        length ++;
    }
    printf("%i\n", length);
}
