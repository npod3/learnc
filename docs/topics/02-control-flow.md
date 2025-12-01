# Control Flow

File: `src/examples/control_flow.c`

What you’ll learn
- `if` / `else` branching
- `switch` statements
- Loops: `for`, `while`, `do { } while`
- `break` / `continue`

Key syntax
- `if (cond) { ... } else { ... }`
- `switch (x) { case 1: ...; break; default: ...; }`
- `for (int i = 0; i < n; ++i) { ... }`

Pitfalls
- Missing `break` in `switch` falls through to next case.
- Off-by-one in loop bounds is common.

Try it
- Add a `continue` for even numbers in the `for` loop.
