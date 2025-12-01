# A15 – Resource Graph

## Overview
Represents dependencies among resources; ensures cleanup in reverse topological order.

## Code Walkthrough
Stub example; real version would build adjacency list and perform DFS for ordering.

## Key Pitfalls
- Cycles causing infinite recursion (detect via visited + stack flags).
- Cleaning resources while dependencies still in use.

## Exercises
1. Implement DFS topological sort for 6 mock resources.
2. Add cycle detection error reporting.

## Further Reading
- Graph algorithms (CLRS).
- Dependency management systems design.
