# 09 – Bitwise Operations

Bitwise operators manipulate individual bits: &, |, ^, ~, <<, >>.

## Common Uses
- Flags: pack booleans into an integer.
- Masks: extract or set subsets of bits.
- Performance: low‑level protocols, compression, graphics.

## Example
```c
#define FLAG_READ  (1u<<0)
#define FLAG_WRITE (1u<<1)
unsigned perms = 0;
perms |= FLAG_READ;          // set read
if (perms & FLAG_READ) { /* ... */ }
perms &= ~FLAG_READ;         // clear read
```

## In `bitwise.c`
Shows combining, clearing, toggling flags and shifting.

## Shifts
- Left (<<): multiply by 2^n (for unsigned).
- Right (>>): divide by 2^n; beware implementation‑defined for signed negatives.

## Pitfalls
- Mixing signed and unsigned; sign extension surprises.
- Over‑shifting: shifting by >= width is undefined.
