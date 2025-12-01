# 20 – ANSI Colors and Terminal Control

ANSI escape codes modify text appearance in terminals supporting them.

## Basic Codes
- Reset: `\x1b[0m`
- Colors: `\x1b[31m` (red), `\x1b[32m` (green), etc.
- Clear screen: `\x1b[2J\x1b[H`

## Example
```c
printf("\x1b[32mSuccess!\x1b[0m\n");
```

## In `ansi_colors.c`
Shows color printing and restoring default state.

## Portability
- Windows older consoles need virtual terminal enable (or use platform abstraction).
- Non‑TTY outputs (redirect to file) will contain raw escape codes.

## Pitfalls
- Forgetting reset → affects subsequent output.
- Chaining codes incorrectly causing unreadable sequences.
