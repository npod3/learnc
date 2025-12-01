# Pointers & Arrays

File: `src/examples/pointers_arrays.c`

What you’ll learn
- Arrays are contiguous memory blocks; `arr[N]`
- `arr` in expressions decays to pointer `&arr[0]`
- `*p` dereferences a pointer; `p+i` walks memory

Key syntax
- Declaration: `int arr[5]; int *p = arr;`
- Indexing: `arr[i]` equals `*(arr + i)`
- Address-of: `&arr[i]`

Pitfalls
- No bounds checking: accessing `arr[5]` is undefined behavior.
- Don’t dereference uninitialized pointers.

Try it
- Print the addresses: `printf("%p %p\n", (void*)&arr[0], (void*)(p+0));`
