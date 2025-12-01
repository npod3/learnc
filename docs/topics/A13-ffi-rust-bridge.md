# A13 – FFI Rust Bridge

## Overview
Expose a C API callable from Rust (`extern "C"` on Rust side). Keep types simple and stable.

## Code Walkthrough
- `c_add` function: pure function with primitive types.
- Would supply a header for bindgen on Rust side.

## Key Pitfalls
- Using C types that map ambiguously in Rust (e.g., `long`).
- Not specifying ownership semantics for pointers returned.

## Exercises
1. Add a context struct with init/destroy and pass pointer back to Rust.
2. Return error codes instead of panicking.

## Further Reading
- Rust FFI Omnibus.
- bindgen crate documentation.
