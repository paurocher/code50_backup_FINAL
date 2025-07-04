pointers
int n = 50;
int *p = &n;

int *p --> this is the syntax to declare a pointer
*p means go to that address and show me what is in there

strings are pointers to the first element of an array of chars!!!
cocnlusion is that strings are "car *name_of_variable"

This is how the type string is defined in cs50 library:
`typedef char *string;`


When comparing two strings, if we do `string_a == string_b` it always returns false because it is indeed comparing two `char *` so it is really comparing two sets of different addresses in the memory (the first letter of each string's memmory address):
```
string str_a = "HI!;
string str_b = "HI!;
str_a == str_b
```
is the same as
```
char *str_a = "HI!";
char *str_b = "HI!";
str_a == str_b
```

returns false



malloc is for allocating memory
free is for freeing p memory, giving it back to the system


valgrind is a terminal command that will tell you if there are any memory leaks.
`valgrind ./03_copy`


Any time a function or line checks for a memmory allocation, we sgould check if it returns NULL, if so, we must return 1 (or any other number) because there was an error allocating that memory. Same when opening files!

Final part of the video is how he built a clone of the 'cp' terminal command. Readinf a file and writing it byte by byte into a nother files.
