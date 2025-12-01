// Purpose: Security basics – bounds checking, integer overflow notes (stub).
// Example Invocation: ID 109

#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int example_security_basics(void){
	printf("[Security Basics]\n");
	unsigned int a = UINT_MAX; unsigned int b = 10;
	printf("Potential overflow if adding b to a: a=%u b=%u\n", a, b);
	if(b > UINT_MAX - a){ printf("Overflow prevented.\n"); }
	char buf[8]; const char *input="abcdefghijkl";
	printf("Safe copy with truncation.\n");
	for(size_t i=0;i<sizeof(buf)-1 && input[i]; i++){
		buf[i]=input[i];
	}
	buf[sizeof(buf)-1]='\0';
	printf("buf=%s\n", buf);
	return 0;
}