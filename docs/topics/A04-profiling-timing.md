# A04 – Profiling & Timing

## Overview
Microbenchmarking with high-resolution timers; importance of warmup and multiple runs.

## Code Walkthrough
- Uses platform monotonic clock abstraction (QueryPerformanceCounter / clock_gettime).
- Runs a loop after warmup.

## Key Pitfalls
- Single measurement variance.
- Compiler optimizations removing dead code (use volatile sink).

## Exercises
1. Add a loop computing mean & standard deviation.
2. Compare -O0 vs -O2 timings.

## Further Reading
- "CPU Microbenchmarking" blog posts.
- Agner Fog optimization manuals.
