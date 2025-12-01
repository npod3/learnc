# A02 – Atomics & Concurrency

## Overview
Introduces C11 atomics for lock-free operations and memory ordering semantics.

## Code Walkthrough
- `_Atomic int counter` with acquire/release.
- False sharing described (adjacent atomics thrash caches).

## Key Pitfalls
- Using `memory_order_relaxed` where ordering needed.
- Assuming atomic operations imply higher-level invariants (they only guarantee atomicity & ordering).

## Exercises
1. Implement a thread increment loop and measure contention.
2. Add padding struct to mitigate false sharing.

## Further Reading
- C11 standard (memory model section).
- Herb Sutter’s atomic ordering articles.
