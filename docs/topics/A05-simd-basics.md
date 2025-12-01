# A05 – SIMD Basics

## Overview
Conditional use of SIMD (SSE2) vs scalar fallback for portability.

## Code Walkthrough
- Checks compile-time macros `USE_SIMD` and `__SSE2__`.
- Falls back gracefully if unsupported.

## Key Pitfalls
- Assuming alignment; loads may fault on unaligned addresses.
- Mixing intrinsics and scalar without consistent reductions.

## Exercises
1. Implement vector addition of 1024 floats with SSE2.
2. Compare scalar vs SIMD timing.

## Further Reading
- Intel Intrinsics Guide.
- Agner Fog optimization manual.
