# Structs & Enums

File: `src/examples/structs_enums.c`

What you’ll learn
- Define types with `struct` and `enum`
- `typedef` to create aliases

Key syntax
- `typedef enum { RED, BLUE } Color;`
- `typedef struct { Color color; char name[16]; } Shirt;`
- Initialize: `Shirt s = { RED, "RedShirt" };`

Pitfalls
- Fixed-size arrays in structs need careful bounds management for strings.

Try it
- Add a new enum value and print it.
