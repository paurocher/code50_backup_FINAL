#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_letters(string plain, string cipher, int key);

int main(int argc, string argv[])
{
    // check arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string test = argv[1];
    int key = atoi(argv[1]);
    // this sucks because on error it returns 0 and I can not differentiate from a 0 the user might
    // choose as a key ... :(
    if (!key)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // prompt for string
    string plain = get_string("plaintext:  ");
    // make anempty array of the same length as the string above and copy the string
    char cipher[strlen(plain)];
    strcpy(cipher, plain);

    // the ciphering function
    rotate_letters(plain, cipher, key);

    printf("ciphertext: %s\n", cipher);

    return 0;
}

void rotate_letters(string plain, string cipher, int key)
{
    // reduce times times to loop for
    int rot = key / 26;
    // add remaining steps
    rot = (key % 26);

    // iterate through each letter
    for (int i = 0; plain[i] != '\0'; i++)
    {
        char letter = plain[i];

        for (int x = 0; x < rot; x++)
        {
            // if it is a letter, otherwise do not change the character
            if isalpha (letter)
            {
                // lowercase
                if (islower(letter))
                {
                    if (letter + 1 > 'z')
                    {
                        letter = 'a' - 0;
                    }
                }
                // uppercase
                else
                {
                    if (letter + 1 > 'Z')
                    {
                        letter = 'A' - 0;
                    }
                }
                letter = letter + 1;
            }
        }
        cipher[i] = letter;
    }
}
