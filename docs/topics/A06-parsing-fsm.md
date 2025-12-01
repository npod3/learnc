# A06 – Parsing FSM

## Overview
Finite State Machine parses a simple digit/operator expression, illustrating token accumulation and state transitions.

## Code Walkthrough
- States: START, NUMBER, OP.
- Accumulate digits; on operator apply previous number with sign.

## Key Pitfalls
- Not handling whitespace or invalid characters (extend states).
- Overflow on large numbers (add range checks).

## Exercises
1. Add whitespace skipping.
2. Support multiplication and division with precedence.

## Further Reading
- Lexers and parsers (Dragon Book basics).
- Pratt parsing for expression precedence.
