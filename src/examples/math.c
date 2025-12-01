// Purpose: Math library and float pitfalls.
#include <stdio.h>
#include <math.h>
int example_math(void){ double v=0.1+0.2; printf("0.1+0.2=%.17f (precision)\n", v); printf("sin(pi)=%.6f\n", sin(3.141592653589793)); return 0; }
