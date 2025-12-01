# 11 – Macros and the Preprocessor

The C preprocessor performs textual substitution before compilation.

## Kinds
- Object‑like: `#define SIZE 32`
- Function‑like: `#define MAX(a,b) ((a)>(b)?(a):(b))`
- Conditional: `#if`, `#ifdef`, `#ifndef`, `#else`, `#endif`

## Example
```c
#ifndef BUILD_DEBUG
#define LOG(msg) ((void)0)
#else
#define LOG(msg) fprintf(stderr, "[debug] %s\n", msg)
#endif
```

## In `macros.c`
Shows parameterized macros, pitfalls (double evaluation), and safe wrapping.

## Safety Guidelines
- Parenthesize parameters and whole macro body.
- Avoid side effects in arguments (`MAX(i++, j++)` is dangerous).
- Prefer inline functions for type safety when possible (C99+).

## Pitfalls
- Multiple evaluations leading to bugs.
- Hidden precedence issues without parentheses.
