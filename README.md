# Learn C by Example

A structured, cross-platform C17 learning project runnable in VS Code. Shows core language features and practical capabilities through small, documented examples plus a terminal Snake game.

## Features
- Menu-driven runner (`main.c`) invoking `example_<topic>()` functions
- Each example: top comment (Purpose, Key Concepts, Compile), inline commentary
- Portable delays and screen clearing (`platform.c`) and platform checks (`#ifdef _WIN32`)
- Threading (C11), sockets (Winsock + POSIX), memory management, file I/O, bitwise ops, function pointers, dynamic arrays, serialization, and more
- Snake game: 20x20 grid, WASD controls, score, self-collision detection
- No undefined behavior executed; pitfalls described only

## Prerequisites
Install a C compiler and VS Code C/C++ extension.

Windows Options:
1. MinGW-w64 (gcc) or LLVM/Clang
2. MSVC Build Tools (Developer Command Prompt)

Linux/macOS:
- System `gcc` or `clang`

VS Code Extensions (recommended):
- ms-vscode.cpptools (C/C++)
- ms-vscode.cpptools-extension-pack (optional)

## Learn by Topics
Start here: `docs/index.md`. It links each example file to a concise explanation of the syntax and patterns used, plus cheat sheets:

- Topics: basics, control flow, pointers & arrays, strings, structs/enums, memory, file I/O, macros, modules, time/random, error handling, function pointers, dynamic arrays, bitwise, threading, sockets, math, game, ANSI colors, build config, serialization.
- Cheat sheets: printf formats, operator precedence.

Open the matching source file under `src/examples/` while reading the guide page.

## Build Commands
Windows (MinGW-w64 / gcc):
```powershell
gcc -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc.exe -lws2_32
```
Windows (Clang via LLVM):
```powershell
clang -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc.exe -lws2_32
```
Windows (MSVC):
```powershell
cl /std:c17 /W4 /EHsc /Fe:bin\learnc.exe /I include src\*.c src\examples\*.c ws2_32.lib
```
Linux/macOS:
```bash
cc -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c src/examples/*.c -o bin/learnc
```

## Run
```powershell
./bin/learnc.exe   # Windows
```
```bash
./bin/learnc       # Linux/macOS
```
Follow on-screen menu to select examples.

If wildcards `*.c` don’t expand in your shell, use the VS Code tasks or `build.ps1`.

## Project Layout
```
learnc/
  README.md
  Makefile
  build.ps1
  include/
    examples.h
    platform.h
  src/
    main.c
    platform.c
    examples/
      basics.c
      control_flow.c
      pointers_arrays.c
      strings.c
      structs_enums.c
      memory.c
      file_io.c
      macros.c
      modules.c
      time_random.c
      error_handling.c
      function_pointers.c
      dynamic_arrays.c
      bitwise.c
      threading.c
      sockets.c
      math.c
      game_snake.c
      ansi_colors.c
      build_config.c
      serialization.c
```

## Style Guide
- Indentation: 4 spaces
- Braces on same line
- `size_t` for indices
- Functions return `int` (0 success) unless naturally returning data
- Avoid global mutable state (except minimal game state)

## Adding a New Example
1. Create `src/examples/<topic>.c`
2. Add prototype to `examples.h`
3. Implement `int example_<topic>(void);`
4. Insert entry in menu table in `main.c`
5. Rebuild

Also add a page under `docs/topics/NN-your-topic.md` explaining:
- Purpose and key concepts
- Key syntax with short code snippets
- Pitfalls and how to avoid them
- “Try it” exercises

## Pitfall Documentation Pattern
In each file, include a comment block:
```
// Pitfalls:
// - Buffer overflow: ...
// - Dangling pointer: ...
// - Double free: ...
```
Never execute UB; show safe alternatives.

## Platform Notes
- Sleep: `platform_sleep_ms()` abstracts Sleep (Win) vs nanosleep (POSIX)
- Clear screen: minimal ANSI attempt; Windows fallback using system("cls") (optional) or ANSI if enabled
- Sockets: Windows requires `WSAStartup`/`WSACleanup` and `-lws2_32`

## Threading
Uses C11 `<threads.h>` if available; if not, file documents fallback instructions.

Tip on MinGW-w64: if `threads.h` is unavailable, the example will report this at runtime; this is expected.

## License
This project is NOT open source. All code, documentation, and assets are Copyright (c) 2025. All rights reserved.

Permitted (non-transferable):
- Personal/local study and experimentation.
- Internal modification for private learning (keep changes private).

Prohibited without prior written permission:
- Redistribution of source or binaries (public repos, gists, packages).
- Commercial use (paid courses, training material, tutorials, books).
- Incorporation into academic curricula or published courseware.
- Creating derivative works for public distribution.

If you wish to negotiate broader rights, contact the author directly.

See `LICENSE.md` for full terms.

## Next Steps
- Implement tests in `/tests` (assert-based) if desired.
- Extend serialization (JSON or binary format) without external libs.

### Advanced Extensions
Additional systems-level examples (IDs 101+): memory advanced (arena & pool allocators), atomics & concurrency, threading queue, profiling & timing, SIMD basics (optional), parsing FSM, modular plugins (dynamic loading concept), binary serialization with endianness, security basics, networking with select(), error strategy (unified error enum), build system notes (Make vs CMake vs Meson), FFI Rust bridge stub, testing harness macro, resource graph cleanup ordering, logging system with atomic level, and an extended Blackjack game with advisor thread & pluggable RNG.

See `docs/architecture.md` for the menu wiring and platform helpers, and `docs/how-to-run-vscode.md` for integrated build/debug.

Enjoy exploring C!