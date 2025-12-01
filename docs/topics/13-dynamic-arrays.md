# 13 – Dynamic Arrays

Manual allocation lets arrays grow at runtime.

## Core Functions
- `malloc(size)`: allocate uninitialized memory.
- `calloc(count,size)`: zero‑initialized block.
- `realloc(ptr,new_size)`: resize keeping contents.
- `free(ptr)`: release.

## Pattern: Doubling Strategy
```c
size_t cap = 8, len = 0;
int *arr = malloc(cap * sizeof *arr);
// push
if (len == cap) {
    cap *= 2;
    arr = realloc(arr, cap * sizeof *arr);
}
arr[len++] = value;
```

## In `dynamic_arrays.c`
Demonstrates push, automatic growth, and cleanup.

## Best Practices
- Always check allocation result for NULL.
- Separate size (length) from capacity.
- Free once; set pointer to NULL after free.

## Pitfalls
- Memory leaks on early returns.
- Using stale pointer after `realloc` failure (handle temp pointer).
