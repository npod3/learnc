# 08 – Error Handling in C

C uses return codes, errno, and defensive checks instead of exceptions.

## Strategies
- Return codes: 0 for success, non‑zero for error.
- Sentinel values: NULL for pointers, -1 for indexes.
- `errno`: set by some library calls (include <errno.h>).
- Wrappers: centralize error logging / mapping.

## Pattern
```c
FILE *f = fopen(path, "r");
if (!f) {
    perror("fopen"); // prints description based on errno
    return 1;
}
```

## In `error_handling.c`
Demonstrates checking return values, using `perror`, and custom messages.

## Recommended Conventions
- Define an enum of error codes for larger programs.
- Keep error reporting at the boundary (I/O, parsing) and propagate simple codes inward.
- Avoid silent failures—log context once.

## Pitfalls
- Forgetting to close resources after failure branches.
- Using `errno` without resetting or checking if function sets it.
- Treating any non‑zero as fatal—allow recoverable errors.
