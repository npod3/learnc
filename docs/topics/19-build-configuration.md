# 19 – Build Configuration

Controlling compilation via flags and conditional code.

## Makefile Targets
- `make` / `make all`: build default.
- `make clean`: remove artifacts.
- May add `DEBUG=1` to enable logging.

## Conditional Compilation
```c
#ifdef DEBUG
    fprintf(stderr, "state=%d\n", state);
#endif
```
Or define from command line: `gcc -DDEBUG ...`.

## In `build_config.c`
Demonstrates toggling features with macros.

## Best Practices
- Centralize feature flags in a single header.
- Keep debug macros lightweight and easily disabled.

## Pitfalls
- Divergent code paths causing untested variants.
- Forgetting to remove sensitive debug output.
