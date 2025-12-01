# A08 – Binary Serialization (Portable)

## Overview
Writes structured data with explicit endianness; avoids compiler padding issues.

## Code Walkthrough
- Converts a 32-bit value to big-endian byte order manually.
- Notes on padding: direct `fwrite(struct)` can record padding bytes.

## Key Pitfalls
- Ignoring endianness across architectures.
- Writing raw structs with padding -> non-portable.

## Exercises
1. Serialize an array of 10 integers with a version header.
2. Add little vs big-endian conversion selection.

## Further Reading
- Network byte order (RFC 1700).
- CBOR / Protocol Buffers design motivation.
