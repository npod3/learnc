# A07 – Modular Plugins

## Overview
Dynamic loading concept: load a shared library at runtime to extend functionality.

## Code Walkthrough
Stub only; real implementation would use `LoadLibrary/GetProcAddress` on Windows and `dlopen/dlsym` on POSIX.

## Key Pitfalls
- ABI drift: struct layout changes break binary compatibility.
- Not validating function pointers before use.

## Exercises
1. Create a plugin exporting `int plugin_add(int,int);`.
2. Load and invoke it conditionally at runtime.

## Further Reading
- Platform docs for dynamic linking.
- Versioning strategies (semantic versioning + capability queries).
