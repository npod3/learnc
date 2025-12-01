// Purpose: Demonstrate layered allocation strategies: system malloc, arena, fixed-size pool.
// Key Concepts: Lifetime management, alignment, fragmentation avoidance, centralized cleanup.
// Build Flags: (none) Optional alignment uses posix_memalign/_aligned_malloc when available.
// Example Invocation: Select ID 101 from menu.
// Pitfalls: Not checking allocation results; improper alignment; double free; fragmentation with many small mallocs.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "advanced/allocator.h"

// Ownership table for cleanup demonstration.
typedef struct Resource { const char *name; void (*cleanup)(void *); void *ptr; } Resource;
static void cleanup_malloc(void *p) { free(p); }
static void cleanup_arena(void *p) { (void)p; /* arena freed once */ }

#define MAX_RES 16
static Resource resources[MAX_RES];
static size_t resource_count = 0;
static void reg(const char *name, void (*fn)(void*), void *ptr){ if(resource_count < MAX_RES){ resources[resource_count++] = (Resource){name,fn,ptr}; }}
static void cleanup_all(void){
    // Free in reverse to respect dependencies.
    for(size_t i = resource_count; i>0; i--){ Resource *r = &resources[i-1]; if(r->cleanup) r->cleanup(r->ptr); }
    resource_count = 0;
}

// --- Arena implementation ---
int arena_init(Arena *a, size_t capacity){ a->base = (unsigned char*)malloc(capacity); if(!a->base) return 0; a->capacity = capacity; a->offset = 0; return 1; }
void *arena_alloc(Arena *a, size_t size, size_t align){ if(align==0) align=1; size_t mask = align-1; size_t off = (a->offset + mask) & ~mask; if(off + size > a->capacity) return NULL; void *ptr = a->base + off; a->offset = off + size; return ptr; }
void arena_reset(Arena *a){ a->offset = 0; }
void arena_free(Arena *a){ free(a->base); a->base=NULL; a->capacity=0; a->offset=0; }

// --- Pool implementation ---
int pool_init(Pool *p, size_t obj_size, size_t capacity){ if(obj_size < sizeof(PoolHeader)) obj_size = sizeof(PoolHeader); p->block = (unsigned char*)malloc(obj_size*capacity); if(!p->block) return 0; p->obj_size = obj_size; p->capacity = capacity; p->free_list = NULL; for(size_t i=0;i<capacity;i++){ PoolHeader *h = (PoolHeader*)(p->block + i*obj_size); h->next = p->free_list; p->free_list = h; } return 1; }
void *pool_alloc(Pool *p){ if(!p->free_list) return NULL; PoolHeader *h = p->free_list; p->free_list = h->next; return h; }
void pool_free(Pool *p, void *ptr){ if(!ptr) return; PoolHeader *h = (PoolHeader*)ptr; h->next = p->free_list; p->free_list = h; }
void pool_destroy(Pool *p){ free(p->block); p->block=NULL; p->capacity=0; p->free_list=NULL; }

// Demo data structures.
typedef struct Vec3 { float x,y,z; } Vec3;
typedef struct Node { int value; struct Node *next; } Node;

static void demo_arena(Arena *arena){
    printf("Arena: allocating 100 Vec3 structs...\n");
    Vec3 *v = (Vec3*)arena_alloc(arena, sizeof(Vec3)*100, alignof(Vec3));
    if(!v){ printf("Arena alloc failed.\n"); return; }
    for(int i=0;i<100;i++){ v[i].x=i; v[i].y=i*2.0f; v[i].z=i*3.0f; }
    printf("Arena offset after alloc: %zu / %zu\n", arena->offset, arena->capacity);
}

static void demo_pool(Pool *pool){
    printf("Pool: allocate linked list nodes...\n");
    Node *head=NULL; for(int i=0;i<10;i++){ Node *n=(Node*)pool_alloc(pool); if(!n){ printf("Pool empty early at %d\n", i); break; } n->value=i; n->next=head; head=n; }
    int count=0; for(Node *cur=head; cur; cur=cur->next) count++;
    printf("Allocated nodes: %d\n", count);
    // Free half
    int freed=0; Node *cur=head; while(cur && freed<5){ Node *next=cur->next; pool_free(pool, cur); cur=next; freed++; }
    printf("Freed %d nodes back to pool.\n", freed);
}

static void fragmentation_note(void){
    printf("\nFragmentation Note:\n");
    printf("Many small malloc/free cycles can fragment the heap; an arena groups lifetimes so a single reset frees many objects at once.\n");
}

int example_memory_advanced(void){
    printf("[Memory Advanced]\n");
    Arena arena; if(!arena_init(&arena, 32*1024)){ printf("Arena init failed\n"); return 1; }
    reg("arena", cleanup_arena, &arena); // freed explicitly later

    Pool pool; if(!pool_init(&pool, sizeof(Node), 64)){ printf("Pool init failed\n"); arena_free(&arena); return 1; }
    reg("pool", (void(*)(void*))pool_destroy, &pool);

    // System malloc example.
    int *arr = (int*)malloc(sizeof(int)*50); if(!arr){ printf("malloc failed\n"); cleanup_all(); arena_free(&arena); return 1; }
    reg("arr", cleanup_malloc, arr);
    for(int i=0;i<50;i++) arr[i]=i*i;
    printf("System malloc array[10]=%d\n", arr[10]);

    demo_arena(&arena);
    demo_pool(&pool);
    fragmentation_note();

    printf("Reset arena (bulk free) then allocate 10 Vec3 again...\n");
    arena_reset(&arena);
    Vec3 *again = (Vec3*)arena_alloc(&arena, sizeof(Vec3)*10, alignof(Vec3));
    if(again) printf("Success. Arena offset=%zu\n", arena.offset);

    // Cleanup order demonstration.
    arena_free(&arena); // remove arena memory
    // Remove arena entry from resources to avoid double free.
    resource_count = 0; // Simplify: we already freed specifics.
    pool_destroy(&pool);
    free(arr);
    printf("Cleanup complete.\n");
    return 0;
}
