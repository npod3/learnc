// Purpose: Simple binary and text serialization of a struct.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct { int id; char name[16]; } Item;
int example_serialization(void){ Item it={42,"Widget"};
    // Text
    FILE*f=fopen("item.txt","w"); if(f){ fprintf(f,"%d %s\n", it.id, it.name); fclose(f);} 
    // Binary
    FILE*b=fopen("item.bin","wb"); if(b){ fwrite(&it,sizeof(it),1,b); fclose(b);} 
    // Read binary
    Item rd; FILE*rb=fopen("item.bin","rb"); if(rb){ fread(&rd,sizeof(rd),1,rb); fclose(rb); printf("Binary read id=%d name=%s\n", rd.id, rd.name);} 
    remove("item.txt"); remove("item.bin"); return 0; }
