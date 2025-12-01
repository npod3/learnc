// Purpose: Demonstrate C11 atomics and contrast with a mutex-protected counter.
// Key Concepts: memory_order variants, false sharing note (comment only).
// Build Flags: (none)
// Example Invocation: ID 102

#include <stdio.h>
#include <stdatomic.h>

int example_atomics_concurrency(void){
    printf("[Atomics & Concurrency] (demo stub)\n");
    // Demonstrate atomic store/load.
    _Atomic int counter = 0;
    atomic_store_explicit(&counter, 42, memory_order_release);
    int v = atomic_load_explicit(&counter, memory_order_acquire);
    printf("Atomic counter value=%d\n", v);
    // False sharing note: adjacent atomics on same cache line can thrash.
    printf("(See docs for thread spawning & false sharing mitigation.)\n");
    return 0;
}
