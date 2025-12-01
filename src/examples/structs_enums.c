// Purpose: Define structs, enums, typedef usage.
#include <stdio.h>
#include <string.h>
typedef enum { COLOR_RED, COLOR_BLUE } Color;
typedef struct { Color color; char name[16]; } Shirt;
int example_structs_enums(void) {
    Shirt s = { COLOR_RED, "RedShirt" };
    printf("Shirt name=%s color=%d\n", s.name, (int)s.color);
    return 0;
}
