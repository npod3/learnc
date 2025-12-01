# A09 – Security Basics

## Overview
Safe patterns: bounds checks, overflow prevention, careful copying.

## Code Walkthrough
- Overflow check before addition.
- Truncated string copy prevents overrun.

## Key Pitfalls
- Using unsafe functions (`strcpy`, `sprintf`) without bounds.
- Integer wrap-around leading to allocation size errors.

## Exercises
1. Implement constant-time string compare.
2. Add input sanitization for a small command parser.

## Further Reading
- CERT C Secure Coding Standard.
- CWE common weakness list.
