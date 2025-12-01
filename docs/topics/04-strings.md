# Strings

File: `src/examples/strings.c`

What you’ll learn
- C strings are NUL-terminated (`'\0'`)
- Safe formatting with `snprintf`
- Getting length with `strlen`

Key syntax
- `char buf[32]; snprintf(buf, sizeof buf, "Hello %s", name);`
- `strlen(buf)` returns characters before `\0`

Pitfalls
- Buffer overflow if writing past array size; always bound your writes.
- `strlen` is O(n); avoid repeated calls in loops.

Try it
- Make the buffer too small and observe truncation from `snprintf`.
