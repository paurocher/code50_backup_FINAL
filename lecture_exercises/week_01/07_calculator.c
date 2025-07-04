# include <cs50.h>
# include <stdio.h>

int add(int a, int b);

int main(void)
{
    int x = get_int("first number: ");
    int y = get_int("second number: ");
    printf("result: %i\n", add(x, y));
}

int add(int a, int b)
{
    return a + b;
}
