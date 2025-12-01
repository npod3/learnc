# A03 – Threading Queue (MPMC)

## Overview
Design of a bounded multi-producer multi-consumer queue with condition variables.

## Code Walkthrough
Stub shows menu hook; real design would include head/tail indices, atomic counts, and signaling.

## Key Pitfalls
- Spurious wakeups: always loop on condition checks.
- Lost wakeups due to not holding mutex when signaling.

## Exercises
1. Implement enqueue/dequeue with a circular buffer.
2. Add backoff strategy when queue full.

## Further Reading
- POSIX pthread condition variables.
- Disruptor pattern (alternative approach).
