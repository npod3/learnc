// Purpose: Macros demonstration.
#include <stdio.h>
#define SQR(x) ((x)*(x))
#define STRINGIFY(x) #x
int example_macros(void) {
    int v=5; printf("SQR(%d)=%d name=%s\n", v, SQR(v), STRINGIFY(SQR));
    return 0;
}
