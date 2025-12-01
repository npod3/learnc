# A11 – Error Strategy

## Overview
Unified error enumeration simplifies propagation and logging.

## Code Walkthrough
- Enum maps discrete states (OK, IO, PARSE, ALLOC).
- Lookup function converts enum to message.

## Key Pitfalls
- Overloaded single error code for different conditions.
- Deep nesting without early returns.

## Exercises
1. Add a stack of context strings for richer messages.
2. Integrate with logging levels.

## Further Reading
- Error handling patterns in C libraries (SQLite, zlib).
