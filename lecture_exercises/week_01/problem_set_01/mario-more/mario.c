#include <cs50.h>
#include <stdio.h>

// function prototype
void draw_line(int size, int counter, bool reverse);

int main(void)
{

    // init size var
    int size = get_int("Size of piramid: ");
    // gates to make size var valid
    if (size < 1 || size > 8)
    {
        do
        {
            printf("Size must be between 1 and 8 (included)\n");
            size = get_int("Size of piramid: ");
        }
        while (size < 1 || size > 8);
    }

    // counter var will be used to do maths with size
    int counter = 0;
    // loop where the drawing happens, driven by the size var
    for (int row = 0; row < size; row++)
    {
        counter++; // counter incrementation
        draw_line(size, counter, false);
        printf("  "); // middle separator
        draw_line(size, counter, true);
        printf("\n"); // new line to continue drawing underneath
    }
}

void draw_line(int size, int counter, bool reverse)
{
    // initial state of the variables
    int hashes = size - counter;
    int spaces = counter;
    char brush_brick = ' ';
    char brush_blank = '#';

    // reversing variable state
    if (reverse)
    {
        hashes = counter;
        spaces = counter;
        brush_brick = '#';
        brush_blank = ' ';
    }

    // hashes
    for (int col = 0; col < hashes; col++)
    {
        printf("%c", brush_brick);
    }
    // spaces
    for (int col = 0; col < spaces; col++)
    {
        printf("%c", brush_blank);
    }
}
