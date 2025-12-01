// Purpose: File I/O (text & binary).
#include <stdio.h>
#include <stdlib.h>
int example_file_io(void) {
    const char *fname="example_tmp.txt";
    FILE *f=fopen(fname,"w"); if(!f){perror("fopen");return 1;} fprintf(f,"Line %d\n",42); fclose(f);
    f=fopen(fname,"r"); if(!f){perror("fopen");return 1;} char line[64]; if(fgets(line,64,f)) printf("Read: %s", line); fclose(f);
    remove(fname); return 0;
}
