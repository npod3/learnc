# A12 – Build System Notes

## Overview
Comparison of Make (manual dependencies), CMake (meta-build generator), Meson (declarative + ninja backend).

## Code Walkthrough
Stub only; discusses flags like `-DDEBUG`, feature toggles with `#ifdef`.

## Key Pitfalls
- Recursive Make inefficiencies.
- Overuse of custom macros hiding build logic.

## Exercises
1. Write a simple CMakeLists.txt for this project subset.
2. Port one example to Meson build definition.

## Further Reading
- "Recursive Make Considered Harmful" paper.
- Official CMake / Meson documentation.
