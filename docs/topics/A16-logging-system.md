# A16 – Logging System

## Overview
Atomic log level field controls verbosity; macros avoid overhead when disabled.

## Code Walkthrough
- `_Atomic int g_log_level` read before printing.
- Macro `LOG(level,msg)` checks threshold.

## Key Pitfalls
- Expensive formatting performed before level check (wrap inside macro condition).
- Data races if non-atomic level variable read concurrently.

## Exercises
1. Add timestamp prefix using platform monotonic time.
2. Implement ring buffer for last N warnings.

## Further Reading
- Structured logging patterns.
- Lock-free ring buffer designs.
