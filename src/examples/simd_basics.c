// Purpose: Illustrate optional SIMD path with SSE2 (if available) vs scalar fallback.
// Build Flags: -DUSE_SIMD (and compiler providing __SSE2__)
// Example Invocation: ID 105

#include <stdio.h>
#include <stdint.h>

int example_simd_basics(void){
    printf("[SIMD Basics]\n");
#ifdef USE_SIMD
#ifdef __SSE2__
    printf("SSE2 path would execute here (stub).\n");
#else
    printf("USE_SIMD defined but __SSE2__ not available; using scalar fallback.\n");
#endif
#else
    printf("Scalar only (compile with -DUSE_SIMD for optional path).\n");
#endif
    return 0;
}
