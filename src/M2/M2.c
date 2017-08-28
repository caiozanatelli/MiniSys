#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "M2.h"

// Initialize the M2 Simulator
void initM2(M2 *vm, int initMemPos) {
	initMemory(vm->memory);
	vm->PC = initMemPos;
	vm->AC = 0;
}

// Load an M2 program into the Simulator memory
void loadProgram(M2 *vm, char *fileDir) {
	FILE *programFile = fopen(fileDir, "r");

	if (!programFile) {
		printf("Error. Program file could not be opened.\n");
		exit(1);
	}

	int memPos = vm->PC;
	Word data = 0;

	// Read the program instructions and load them into the Simulator memory
	while (fscanf(programFile, "%d", &data) == 1) {
		writeMemory(vm->memory, data, memPos++);
	}
}

void runProgram(M2 *vm) {
	Word firstByte = 0, secondByte = 0;
	int input = 0, pos = 0, memValueAtPos = 0;

	do {
		// Read an instruction from memory and updates the program counter
		readMemory(vm->memory, &firstByte, vm->PC);
		readMemory(vm->memory, &secondByte, vm->PC + 1);
		vm->PC += 2;

		// Get the memory position to be read/written
		pos = vm->PC + secondByte;

		// Identify the current instruction and execute it
		switch (firstByte) {
			case LAD:
				readMemory(vm->memory, &vm->AC, pos);
			break;

			case SAD:
				writeMemory(vm->memory, vm->AC, pos);
			break;

			case ADD:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->AC += memValueAtPos;
			break;

			case SUB:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->AC -= memValueAtPos;
			break;

			case INP:
				scanf("%d", &input);
				writeMemory(vm->memory, input, pos);
			break;

			case OUT:
				readMemory(vm->memory, &memValueAtPos, pos);
				printf("%d\n", memValueAtPos);
			break;

			case JMP:
				vm->PC = pos;
			break;

			case JGZ:
				if (vm->AC > 0) {
					vm->PC = pos;
				}
			break;

			case JLZ:
				if (vm->AC < 0) {
					vm->PC = pos;
				}
			break;

			case JZE:
				if (vm->AC == 0) {
					vm->PC = pos;
				}
			break;

			case HLT:
				// End of program
			break;

			default:
				printf("Error. Unrecognized instruction.\n");
				exit(1);
			break;
		}

	} while (firstByte != HLT);

}