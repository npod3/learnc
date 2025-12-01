# A01 – Memory Advanced (Allocator Layering)

## Overview
Demonstrates combining system `malloc` with an arena (bump allocator) and a fixed-size pool to manage lifetimes and reduce fragmentation.

## Code Walkthrough
- Arena: contiguous block; allocations bump an offset; bulk free via reset.
- Pool: pre-allocated fixed-size objects; freelist for O(1) alloc/free.
- Ownership table: registers allocated resources and cleans up in reverse.

## Key Pitfalls
- Forgetting alignment: misaligned data leads to UB on some architectures.
- Double free: centralize ownership to avoid multiple frees.
- Reallocating after arena free (pointer invalid).

## Exercises
1. Add alignment enforcement for 16-byte objects.
2. Track peak usage of the arena.
3. Implement fallback to system malloc if arena exhausted.

## Further Reading
- “Game Engine Architecture” – memory arenas.
- allocators in jemalloc / mimalloc (contrast).
