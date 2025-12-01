# A14 – Testing Harness

## Overview
Minimal in-source test macro system for quick validation.

## Code Walkthrough
- `TEST(name)` macro defines function taking fail counter.
- Runner accumulates failures and reports count.

## Key Pitfalls
- Not isolating test side-effects.
- Missing diagnostic detail (consider expected vs actual prints).

## Exercises
1. Add macro `ASSERT_EQ(a,b)` with line number.
2. Color output using ANSI (enable Windows VT mode).

## Further Reading
- Unity test framework (lightweight C harness).
- GoogleTest (contrast heavier approach).
