Hello there, this repo is my first programming project, i realised a calulator using command line built in C. 
It manages basic operations like '+,-,*,/,%,^".

This calculator also handles parenthetical priorities.

I implemented a file that acts as a parser, meaning it identifies the characters entered on the command line by the user.
Then there's a file that evaluates expressions. This is the crucial part of the calculator. It evaluates operator priorities and stores the prioritized operators in stacks, along with the associated numbers. This file then calculates them and returns the result of the operation.
And a main.c file that represents the "user interface." The results of the operations are displayed there.
