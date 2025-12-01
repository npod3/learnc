# 18 – Math Library and Floating Point

C `<math.h>` provides common functions; link with `-lm` on some platforms.

## Common Functions
- `sqrt`, `pow`, `sin`, `cos`, `tan`
- `fabs`, `floor`, `ceil`
- `exp`, `log`, `log10`

## Floating Point Caveats
- Precision: `float` (~7 digits), `double` (~15 digits).
- Equality: compare with epsilon.
```c
if (fabs(a - b) < 1e-9) { /* equal */ }
```

## In `math.c`
Shows typical usage and printing with format specifiers.

## Pitfalls
- Ignoring domain errors (e.g. `sqrt(-1)` returns NaN).
- Not checking overflow/underflow for extreme inputs.
