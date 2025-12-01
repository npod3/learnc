# Memory Management

File: `src/examples/memory.c`

What you’ll learn
- Dynamic allocation: `malloc`, `calloc`, `realloc`, `free`
- Growth patterns and ownership

Key syntax
- `int *a = malloc(n * sizeof *a);`
- `a = realloc(a, new_n * sizeof *a);`
- `int *c = calloc(n, sizeof *c); // zero-initialized`

Pitfalls
- Always check allocation results before use.
- After `realloc`, previous pointer is invalid (use the returned value).
- Double `free` and use-after-free are undefined behavior.

Try it
- Intentionally fail allocation by using a huge size and handle the error.
