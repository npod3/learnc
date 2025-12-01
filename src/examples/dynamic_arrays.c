// Purpose: Manual dynamic array growth.
#include <stdio.h>
#include <stdlib.h>
int example_dynamic_arrays(void){
	size_t cap=4, len=0;
	int *arr = (int*)malloc(cap*sizeof(int));
	if(!arr) return 1;
	for(int v=0; v<10; ++v){
		if(len==cap){
			cap*=2;
			int *tmp = (int*)realloc(arr, cap*sizeof(int));
			if(!tmp){ free(arr); return 1; }
			arr = tmp;
		}
		arr[len++] = v;
	}
	for(size_t i=0;i<len;++i){
		printf("arr[%zu]=%d\n", i, arr[i]);
	}
	free(arr);
	return 0;
}
