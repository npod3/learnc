// Purpose: High-resolution timing & microbenchmark pitfalls.
// Key Concepts: Warmup, variability, simple timing harness.
// Example Invocation: ID 104

#include <stdio.h>
#include <time.h>
#include <stdint.h>

static uint64_t monotonic_ns(void){
#if defined(_WIN32)
    LARGE_INTEGER freq, counter; QueryPerformanceFrequency(&freq); QueryPerformanceCounter(&counter);
    return (uint64_t)(counter.QuadPart * 1000000000ull / freq.QuadPart);
#else
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (uint64_t)ts.tv_sec*1000000000ull + ts.tv_nsec;
#endif
}

int example_profiling_timing(void){
    printf("[Profiling & Timing]\n");
    // Warmup
    volatile int sink=0; for(int i=0;i<100000;i++) sink+=i;
    uint64_t start = monotonic_ns();
    for(int i=0;i<200000;i++) sink+=i;
    uint64_t end = monotonic_ns();
    printf("Elapsed ~%llu ns (sink=%d)\n", (unsigned long long)(end-start), sink);
    printf("Note: Single run unreliable; run multiple iterations & compute stats.\n");
    return 0;
}
