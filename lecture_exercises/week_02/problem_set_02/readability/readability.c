#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_grade(float letters, float words, float sentences);
void print_output(int index);

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char letter = text[i];
        if (isalpha(letter))
        {
            letters++;
        }
        else if (ispunct(letter) || isspace(letter))
        {
            if (letter == '?' || letter == '!' || letter == '.') // phrase or word end
            {
                words++;
                sentences++;
            }
            else if (letter == ' ' || letter == ',') // word end
            {
                if (isalpha(text[i - 1]))
                {
                    words++;
                }
            }
        }
    }
    int index = compute_grade((float) letters, (float) words, (float) sentences);
    print_output(index);
}

int compute_grade(float letters, float words, float sentences)
{
    // int to float conversion

    float L = letters / words * 100.;
    float S = sentences / words * 100.;

    // compute grade index
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

void print_output(int index)
{
    // print grade depending on the index
    if (index < 1)
    {
        printf("Before Grade: 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}
