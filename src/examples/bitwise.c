// Purpose: Bitwise flags.
#include <stdio.h>
#define FLAG_READ  (1u<<0)
#define FLAG_WRITE (1u<<1)
#define FLAG_EXEC  (1u<<2)
int example_bitwise(void){ unsigned perms=FLAG_READ|FLAG_WRITE; if(perms & FLAG_READ) printf("read set\n"); perms ^= FLAG_WRITE; printf("after toggle write=%u\n", (perms & FLAG_WRITE)!=0); return 0; }
