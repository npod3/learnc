// Purpose: Control flow structures (if, switch, loops, break/continue).
// Key Concepts: if/else, switch with enum, for/while/do-while, loop control.
// Compile: see README.
#include <stdio.h>
#include <stdlib.h>
int example_control_flow(void) {
    printf("== Control Flow ==\n");
    int x = 5;
    if (x > 3) printf("x > 3\n"); else printf("x <= 3\n");
    switch (x) {
        case 1: printf("one\n"); break;
        case 5: printf("five\n"); break;
        default: printf("other\n"); break;
    }
    int sum = 0;
    for (int i = 0; i < 5; ++i) sum += i;
    printf("sum 0..4=%d\n", sum);
    int i = 0; while (i < 3) { printf("while i=%d\n", i); ++i; }
    int j = 0; do { printf("do-while j=%d\n", j); ++j; } while (j < 2);
    return 0;
}
