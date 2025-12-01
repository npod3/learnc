# 17 – Time and Random

Working with clocks and random numbers.

## Time
- Wall clock: `time(NULL)` seconds since epoch.
- High‑resolution / monotonic: platform specific; abstraction provided in `platform.c`.

## Random
- `rand()` low quality; use better algorithm for serious use.
- Seed: `srand((unsigned)time(NULL));`

## In `time_random.c`
Demonstrates seeding and generating values, plus measuring elapsed time.

## Best Practices
- Prefer monotonic timer for measuring intervals.
- Avoid modulo bias (`rand() % n`). Use rejection sampling for uniformity when needed.

## Pitfalls
- Reseeding repeatedly → correlated sequences.
- Assuming `rand()` is cryptographically secure (it is not).
