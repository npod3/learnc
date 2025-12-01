// Purpose: Platform detection with preprocessor.
#include <stdio.h>
int example_build_config(void){
#ifdef _WIN32
    printf("Windows platform detected.\n");
#else
    printf("POSIX-like platform detected.\n");
#endif
    return 0; }
