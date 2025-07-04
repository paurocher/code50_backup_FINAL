# include <stdio.h>

/*
here we create a fuction that returns no value and gets"
an int as a parameter"
*/

void meow(int);
/*to leave main at the top, we can declare empty functions that main will call
at the top so it does not complain to us. Otherwise main would be looking for
functions that are not declared yet and the compiler would complain.
This is called a prototype.*/

/*According to the C and C++ standards, the return type of main() should be int.
This indicates the program's execution status to the environment it runs in,
with 0 typically signifying successful completion.*/

int main(void)
{
    meow(2);
}

void meow(int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("meow\n");
    }
}

