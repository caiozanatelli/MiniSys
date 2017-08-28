#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Memory.h"

#define isMemPosValid(pos) (pos >= 0 && pos < MAX_MEM)

void initMemory(Memory memory) {
	memset(memory, 0, MAX_MEM * sizeof(Word));
}

void printMemory(Memory memory) {
	printf("--------------\n");
	printf(". : Memory : . \n\n");
	
	int i;
	for (i = 0; i < MAX_MEM; i++) {
		printf("Memory[%d]: %u\n", i, memory[i]);
	}

	printf("--------------\n\n");
}

int writeMemory(Memory memory, Word data, int pos) {
	if (!isMemPosValid(pos)) {
		printf("Data could not be written into memory. The requested position is invalid.\n");
		return FALSE;
	}

	memory[pos] = data;
	return TRUE;
}

Word readMemory(Memory memory, Word *data, int pos) {
	if  (!isMemPosValid(pos)) {
		printf("Data could not be read from memory. The requested position is invalid.\n");
		return FALSE;
	}

	*data = memory[pos];

	return TRUE;
}
