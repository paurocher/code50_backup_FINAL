Get into the habit of using the debugger!!"
1. compile your code
`
make code_file.c
debug50 code_file
`

We can use the initialisation of a for loop to declare a new variable using a function. The init just runsonce before the loop starts.
'for (int i = 0; i < strlen(s); i++)' Here we ask the length of s at each iteratin over the loop
'for (int i = 0, n = strlen(s); i < n; i++)' Here, we declare n in the init of the loop, hence it is just processed once!!

Declaring arrays:
`
int scores[3]
scores[0] = 'apple';
scores[1] = 'banana';
scores[2] = 'orange';
`
`
int fruits[] = {'apple', 'banana', 'orange'}
`

We can not change the size of an array on the fly.
WE can not copy arrays t another variable. To do that we have to use a loop.
If we pass an array to a function, that does not become a copy of the variable in the function as happens with any other variable, that is the actual same variable it becomes a reference!


libs to check:
cs50
stdio
string
ctype


Any program reurns a number on exit. If it is 0, all is good, otherwise it is an error, it is bad!
We can 'echo $?' to get the velue returned by the program.


arguments:
argc (argument count) is the numbers of arguments passed
argv (argument vector) is an array with all the arguments passed, including at position 0, the name of the program. These arguments always come in as strings!


local and global variables
globals are declared outside of any functions.
