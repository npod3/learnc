# 14 – Serialization Basics

Serialization transforms in‑memory structures into a portable byte or text format.

## Approaches
- Text (CSV, JSON‑like): human readable, slower.
- Binary (struct write): fast, needs endianness care.

## Example (Binary Struct)
```c
struct Point { int x, y; } p = {10,20};
fwrite(&p, sizeof p, 1, fp);
```

## In `serialization.c`
Shows writing simple records and reading them back, plus validating counts.

## Portability Concerns
- Endianness: use explicit byte order for cross‑platform.
- Padding: compiler may insert padding bytes; avoid direct `fwrite` for portable storage or pack manually.

## Best Practices
- Include version tag in file header.
- Validate read sizes; never trust file length.
- Use checksums for integrity when needed.
