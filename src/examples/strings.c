// Purpose: C strings and safer handling.
// Key Concepts: null terminator, strlen, snprintf.
#include <stdio.h>
#include <string.h>
int example_strings(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Hello %s", "World");
    printf("%s (len=%zu)\n", buf, strlen(buf));
    return 0;
}
