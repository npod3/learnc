// Purpose: Binary serialization with endianness awareness (simplified).
// Example Invocation: ID 108

#include <stdio.h>
#include <stdint.h>

static uint32_t to_be32(uint32_t v){
	unsigned char b[4]={ (unsigned char)(v>>24), (unsigned char)(v>>16), (unsigned char)(v>>8), (unsigned char)v };
	return (uint32_t)b[0]<<24 | (uint32_t)b[1]<<16 | (uint32_t)b[2]<<8 | b[3];
}

int example_serialization_binary(void){
	printf("[Binary Serialization] (stub) value endianness demo.\n");
	uint32_t x = 0x11223344; uint32_t be = to_be32(x);
	printf("x=0x%08X be=0x%08X\n", x, be);
	return 0;
}