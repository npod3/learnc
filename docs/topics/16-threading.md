# 16 – Threading

C11 adds `<threads.h>` (optional). Platform APIs (pthreads, Win32) are common.

## Concepts
- Thread creation/run function.
- Shared data + synchronization (mutexes, atomics).
- Data races: unsynchronized concurrent writes/reads.

## Example (Pseudo C11)
```c
thrd_t t;
thrd_create(&t, worker, &arg);
thrd_join(t, NULL);
```
If `<threads.h>` unavailable, emulate with platform layer.

## In `threading.c`
Shows conceptual usage; may compile with a macro disabling threads on unsupported toolchains.

## Synchronization Tools
- Mutex: mutual exclusion.
- Atomic ops: lock‑free counters.
- Condition variables: wait + signal.

## Pitfalls
- Forgetting to join threads (resource leak).
- Holding locks across blocking I/O.
