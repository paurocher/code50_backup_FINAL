#include <stdio.h>

void swap (int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is: %i, y is: %i\n", x, y);
    swap(&x, &y);
    printf("x is: %i, y is: %i\n", x, y);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


// This does have the expected result (swap x and y) because we are passing the variable as reference instead as of value.
// The &  and * allow us to pass the memory locator and read the memmory locator respectively.
