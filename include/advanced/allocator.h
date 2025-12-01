#ifndef LEARNC_ADVANCED_ALLOCATOR_H
#define LEARNC_ADVANCED_ALLOCATOR_H

// Simple educational arena + fixed-size pool allocators.
// Not thread-safe; demonstrates layering over system malloc.

#include <stddef.h>
#include <stdint.h>

typedef struct Arena {
    unsigned char *base;
    size_t capacity;
    size_t offset;
} Arena;

int arena_init(Arena *a, size_t capacity);
void *arena_alloc(Arena *a, size_t size, size_t align); // align must be power of two
void arena_reset(Arena *a); // keeps memory, rewinds offset
void arena_free(Arena *a);  // releases memory

typedef struct PoolHeader { struct PoolHeader *next; } PoolHeader;

typedef struct Pool {
    unsigned char *block;
    size_t obj_size;
    size_t capacity;
    PoolHeader *free_list;
} Pool;

int pool_init(Pool *p, size_t obj_size, size_t capacity);
void *pool_alloc(Pool *p);
void pool_free(Pool *p, void *ptr);
void pool_destroy(Pool *p);

#endif // LEARNC_ADVANCED_ALLOCATOR_H
