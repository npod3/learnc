// Purpose: Demonstrate C API surface suitable for Rust FFI (stub).
// Example Invocation: ID 113

#include <stdio.h>
#include <stdint.h>

// Exported functions would be declared in a header consumed by Rust via bindgen.
// extern "C" applies on the Rust side; C compiler does not need special syntax.

int c_add(int a, int b){ return a+b; }

int example_ffi_rust_bridge(void){
    printf("[FFI Rust Bridge] c_add(2,3)=%d\n", c_add(2,3));
    return 0;
}
