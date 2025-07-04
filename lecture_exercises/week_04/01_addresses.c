#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;

    printf("%p\n", p);
    printf("%i\n", *p);

    // strings are pointers to first element of a char array
    string s = "HI!";
    printf("%p\n\n", s);

    //proof the first char of the string array is the same
    printf("%p\n\n", &s[0]);

    //so strings are pointers to a char * array:
    // this is the c way. We can use 'string' thanks to the cs50 library, but in theory
    // string does not exist in c :D
    char *ss = "HELLO!";
    printf("%s\n\n", ss);


    // pointer arithmetic
    char *sss = "HI!";
    printf("%c", *s);
    printf("%c", *(s + 1));
    printf("%c\n", *(s + 2));

}
