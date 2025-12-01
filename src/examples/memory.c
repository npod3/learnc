// Purpose: Dynamic memory allocation (malloc/free/realloc/calloc).
#include <stdio.h>
#include <stdlib.h>
int example_memory(void) {
    size_t n=5; int *a=(int*)malloc(n*sizeof(int));
    if(!a){perror("malloc");return 1;} for(size_t i=0;i<n;++i)a[i]=(int)i;
    int *b=(int*)realloc(a, n*2*sizeof(int)); if(!b){free(a);return 1;} a=b; for(size_t i=n;i<2*n;++i)a[i]=(int)i;
    int *c=(int*)calloc(3,sizeof(int)); if(!c){free(a);return 1;} // zero-initialized
    printf("realloc size=%zu last=%d calloc[0]=%d\n", n*2, a[2*n-1], c[0]);
    free(a); free(c); return 0;
}
