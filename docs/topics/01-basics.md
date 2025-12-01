# Basics

File: `src/examples/basics.c`

What you’ll learn
- Primitive types: `int`, `unsigned`, `long`, `float`, `double`, `char`, `size_t`
- Initialization vs assignment
- Arithmetic, relational, logical, and bitwise operators
- `const` correctness
- Scope and shadowing
- Casting and integer vs floating point division

Key syntax
- Declarations: `int a = 10;` declares and initializes an `int`.
- Literals: `42u` (unsigned), `1000L` (long), `3.14f` (float suffix), `2.71` (double default).
- Format specifiers (printf): `%d` int, `%u` unsigned, `%ld` long, `%f` double, `%c` char, `%zu` size_t.
- Casting: `(double)a / (double)b` promotes to floating division.

Pitfalls
- Uninitialized variables have indeterminate values.
- Integer division truncates; cast to double for precise division.
- Signed overflow is undefined; unsigned overflow wraps modulo 2^N.

Try it
- Change `a` and `ua` and observe `quot` vs `precise`.
- Add a new variable `long long big = 1LL<<40;` and print with `%lld`.
