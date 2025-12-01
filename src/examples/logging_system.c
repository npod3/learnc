// Purpose: Multi-level logger with atomic level (stub).
// Example Invocation: ID 116

#include <stdio.h>
#include <stdatomic.h>

static _Atomic int g_log_level = 1;
#define LOG(lvl,msg) do{ if((lvl)<=atomic_load(&g_log_level)) printf("[L%d] %s\n", (lvl), (msg)); }while(0)

int example_logging_system(void){
	LOG(1,"Info message");
	LOG(2,"Verbose detail (hidden by default)");
	atomic_store(&g_log_level, 2);
	LOG(2,"Now visible after level raise");
	return 0;
}