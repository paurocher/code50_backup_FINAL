// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    SAMPLE s;

    // Copy header from input file to output file
    // 44 bytes (8 bits) is 22 SAMPLES (16 bits)
    for (int i = 0; i < 22; i++)
    {
        if (fread(&s, sizeof(s), 1, input))
        {
            fwrite(&s, sizeof(s), 1, output);
        }
    }

    // TODO: Read samples from input file and write updated data to output file
    while (fread(&s, sizeof(s), 1, input))
    {
        SAMPLE a = s * factor;
        // printf("%u\n", s);
        fwrite(&a, sizeof(s), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
