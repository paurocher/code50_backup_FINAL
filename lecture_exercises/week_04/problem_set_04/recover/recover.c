#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// // define datatype BYTE
// typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // verify arguments
    if (argc != 2)
    {
        printf("Usage: recover [forensic image file]\n");
        return 1;
    }

    // open memory card
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        printf("File \'%s\' not found\n", argv[1]);
        return 1;
    }

    // create buffer of 512 bytes
    uint8_t buffer[512];
    // printf("sizeof buffer: %lu\n", sizeof(buffer));

    int found_jpg_header = 0; // bool tracking if we have found a new jpg header
    int jpg_files_count = 0;  // keep track of amount of created jg files
    char dest_file_name[8];   // array of 8 chars. Enough room for "xxx.jpg" + string end char
    FILE *dest_file = NULL; // placeholder for the destination file. Created here so it is
                            // reachable in all scopes of the following while and if statements stack.

    // repeat until end of card
    while (fread(buffer, 1, 512, card))
    {
        // if jpg header detected
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpg_header = 1; // set bool to true
        }
        // if we are in a jpg file keep saving bytes into a file
        if (found_jpg_header == 1)
        {
            // if this is not the first found jpg file, then close the file as a new header has been
            // found and we are going to create a new file.
            if (jpg_files_count != 0)
            {
                fclose(dest_file);
            }
            sprintf(dest_file_name, "%03i.jpg", jpg_files_count); // build file name
            dest_file = fopen(dest_file_name, "w");
            fwrite(buffer, 1, 512, dest_file);
            jpg_files_count++;
            found_jpg_header =
                0; // to false so we work on writing to disk (in  the condition below)
        }
        // if not new jpg file, write to file
        else if (jpg_files_count != 0)
        {
            fwrite(buffer, 1, 512, dest_file);
        }
    }
    // close any remaining open file
    fclose(dest_file);
    fclose(card);

    return 0;
}
