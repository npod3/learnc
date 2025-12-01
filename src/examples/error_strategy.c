// Purpose: Unified error enum & mapping concept (stub).
// Example Invocation: ID 111

#include <stdio.h>

enum LearnError { LE_OK=0, LE_IO, LE_PARSE, LE_ALLOC };
static const char *le_str(enum LearnError e){ switch(e){ case LE_OK: return "OK"; case LE_IO: return "IO"; case LE_PARSE: return "PARSE"; case LE_ALLOC: return "ALLOC"; default: return "?"; } }

int example_error_strategy(void){
    enum LearnError e = LE_PARSE;
    printf("[Error Strategy] code=%d msg=%s\n", e, le_str(e));
    return 0;
}
