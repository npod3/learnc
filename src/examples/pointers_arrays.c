// Purpose: Demonstrate pointers, arrays, and pointer arithmetic.
// Key Concepts: address-of, dereference, arrays decay to pointer, iteration.
#include <stdio.h>
#include <stddef.h>
int example_pointers_arrays(void) {
    int arr[5] = {1,2,3,4,5};
    int *p = arr; // arr decays to &arr[0]
    for (size_t i=0;i<5;++i) {
        printf("arr[%zu]=%d *(p+%zu)=%d\n", i, arr[i], i, *(p+i));
    }
    return 0;
}
