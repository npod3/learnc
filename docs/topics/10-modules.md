# 10 – Modules and Translation Units

C organizes code via separate .c/.h pairs compiled independently then linked.

## Separation Goals
- Encapsulation: expose only necessary declarations in headers.
- Rebuild efficiency: change one module, recompile it only.
- Namespace cleanliness: use prefixes to avoid collisions.

## Pattern
Header `foo.h`:
```c
#ifndef FOO_H
#define FOO_H
int foo_add(int a, int b);
#endif
```
Source `foo.c`:
```c
#include "foo.h"
int foo_add(int a, int b) { return a + b; }
```

## In `modules.c`
Demonstrates internal (static) functions vs exported ones.

## Best Practices
- Guard headers with include guards.
- Never define storage in headers (except `extern` declarations).
- Keep headers minimal and dependency‑light.

## Pitfalls
- Circular includes → forward declare structs instead.
- Multiple definition errors from definitions in headers.
