big O notation describes how fast or slow the algorithm is going to be:
 - linear search --> O(n)
 - binary search --> O(log n)

Omega represents the lower bound, how quick an algorithm can get done (might take as few steps as ...):
 - linear search --> Omega 1
 - binary search --> Omega 1

If big O and omega happen to be the same we can describe the algorith as Theta:
 - counting to n --> theta(n) (the amounts of steps to solve is the same in bif O and Omega)



 creating our own datatype:
 '''
 typedef struct
 {
    string name;
    string number;
 } person;
'''
Notice, the right style is for "person" to be on the same line as the closing curly bracket.



Sorting algorithms:
- selection sort: look for the smallest. On big O it's: O(n squared). It's slow :) On Omega it's also: Omega(n squared), even if we are lucky and the array is all sorted, it will stil go through all the process and steps. Hence it is in Theta(n squared), because big O and Omega are the same.

- buble sort (like bubbles rising at the top of a glass): compares adjacent numbers. Very slow as wel ...

- merge sort: divide the list by 2, sort both halves and merge them. Mergin them is: compare the firsts 2 numbers, put the smallest one on a new list and remove it form the old (or go to the next ont), again compare the first two numbers and put the smallest one in that new list and remove it from the old, ... It uses recursion!!
We can create many more arrays to organize the numbers. So instead of just keeping 1 number in memory to compare with another, we can compare many at once!
It is "n * log * n" in big O and Omega, thus Theta as well ...
