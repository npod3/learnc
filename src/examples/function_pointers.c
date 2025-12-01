// Purpose: Function pointers and callbacks.
#include <stdio.h>
static int add(int a,int b){return a+b;}
static int mul(int a,int b){return a*b;}
static int apply(int (*op)(int,int), int x, int y){return op(x,y);} 
int example_function_pointers(void){ printf("add=%d mul=%d\n", apply(add,2,3), apply(mul,2,3)); return 0; }
