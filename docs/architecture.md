# Project Architecture

- `src/main.c`: Menu runner that maps a number to an `example_<topic>()` function.
- `include/examples.h`: Central list of example prototypes.
- `src/examples/`: Each topic in its own file. Each example returns `int` (0 = success).
- `include/platform.h` + `src/platform.c`: Small cross-platform helpers: sleep, time, screen clear, non-blocking input.

Flow
1. `main.c` prints a menu (`examples[]` table).
2. Reads the selection and calls the function pointer.
3. Each example prints its output and returns to the menu.

Design choices
- No external dependencies: only standard C and minimal platform APIs.
- Examples are self-contained: easy to open a single file and study.
- Warnings enabled: code compiles cleanly to encourage best practices.

Extending
- Add a new `src/examples/foo.c` and its prototype in `include/examples.h`.
- Add an entry in `examples[]` in `src/main.c`.
- Document it under `docs/topics`.
