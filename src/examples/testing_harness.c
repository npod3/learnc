// Purpose: Minimal testing harness concept (stub).
// Example Invocation: ID 114

#include <stdio.h>
#include <string.h>

#define TEST(name) static void name(int *fails)

TEST(test_add){ int a=2+3; if(a!=5){ (*fails)++; printf("fail: test_add\n"); } }

int example_testing_harness(void){
	int fails=0; test_add(&fails);
	printf("[Testing Harness] fails=%d\n", fails);
	return 0;
}