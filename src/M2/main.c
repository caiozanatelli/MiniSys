#include <stdlib.h>
#include <stdio.h>
#include "M2.h"

#define POS_FILE_DIR	1
#define POS_INIT_MEM	2

int main(int argc, char **argv) {
	
	// Make sure that all parameters are right
	if (argc != 3) {
		printf("Error. Incorrect parameters.\n");
		exit(1);
	}

	// Get the initial position to write instructions into memory
	int memPos;
	sscanf(argv[POS_INIT_MEM], "%d", &memPos);

	// Create an instance of an M2 Simulator
	M2 vm;
	initM2(&vm, memPos);

	// Load a program into memory and execute it through an M2 Simulator
	loadProgram(&vm, argv[POS_FILE_DIR]);

	//printMemory(vm.memory);
	runProgram(&vm);
	//printMemory(vm.memory);

	return 0;
}