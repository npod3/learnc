# Run in VS Code

Requirements
- Install one toolchain: MSVC, MinGW-w64 GCC (MSYS2), or LLVM Clang.
- Ensure the compiler is on PATH (see README).

Build
- Terminal → Run Build Task → choose one: Build (MSVC), Build (gcc), Build (Clang).
- Or run `build.ps1 -Compiler cl|gcc|clang` in PowerShell (enable script execution if needed).

Debug
- Run and Debug panel → pick: Run learnc (MSVC|gcc|Clang).
- The app opens in an external console.

Tips
- If wildcards `src/*.c` don’t expand in PowerShell tasks, use the provided tasks or `build.ps1`.
- On MinGW, `threads.h` may be unavailable; the threading example prints a notice instead.
