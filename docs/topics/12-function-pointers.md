# Function Pointers

File: `src/examples/function_pointers.c`

What you’ll learn
- Declare and pass functions as parameters
- Build a simple dispatcher

Key syntax
- Declaration: `int (*op)(int,int) = add;`
- Call through pointer: `op(2,3)`
- Pass to a function: `apply(op, x, y)`

Pitfalls
- Function pointer signatures must match exactly.

Try it
- Add a `sub` function and route based on user input.
