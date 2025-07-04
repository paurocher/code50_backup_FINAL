#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int phrases = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char letter = text[i];
        printf("%c\n", letter);
        if (isalpha(letter))
        {
            printf("isalpha\n");
        }
        if (ispunct(letter))
        {
            printf("ispunct\n");
        }
        printf("\n");
    }
}
