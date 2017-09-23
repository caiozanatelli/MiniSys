#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "M2.h"

// Initialize the M2 Simulator
void initM2(M2 *vm, int initMemPos) {
	initMemory(vm->memory);

	vm->initialPos = initMemPos;
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

	fclose(programFile);
}

// Run an M2 program until the HLT instruction is found
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
		
		//printf("[%d %d]\n", firstByte, secondByte); // debug-off

		// Identify the current instruction and execute it
		switch (firstByte) {
		
			// Load AC directly: AC <- (M)
			case LAD:
				readMemory(vm->memory, &vm->AC, pos);
			break;

			// Store AC directly: (M) <- AC
			case SAD:
				writeMemory(vm->memory, vm->AC, pos);
			break;

			// Save sum to AC: AC <- AC + (M)
			case ADD:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->AC += memValueAtPos;
			break;

			// Save subtraction to AC: AC <- AC - (M)
			case SUB:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->AC -= memValueAtPos;
			break;

			// Read an inter: (M) <- integer read
			case INP:
				scanf("%d", &input);
				writeMemory(vm->memory, input, pos);
			break;

			// Print the value of an address position: Print (M)
			case OUT:
				readMemory(vm->memory, &memValueAtPos, pos);
				printf("%d\n", memValueAtPos);
			break;

			// Jump to the address given: PC <- M
			case JMP:
				vm->PC = pos;
			break;

			// Jump on greater than zero: if AC > 0 then PC <- M
			case JGZ:
				if (vm->AC > 0) {
					vm->PC = pos;
				}
			break;

			// Jump on less than zero: if AC < 0 then PC <- M
			case JLZ:
				if (vm->AC < 0) {
					vm->PC = pos;
				}
			break;

			// Jump on equal to zero: if AC == 0 then PC <- M
			case JZE:
				if (vm->AC == 0) {
					vm->PC = pos;
				}
			break;

			// Stop execution
			case HLT:
				// End of program
			break;

			// Direct load: RX <- (M)
			case LXD:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->RX = memValueAtPos;
			break;

			// Direct store: (M) <- RX
			case SXD:
				writeMemory(vm->memory, vm->RX, pos);
			break;

			// Indexed load: AC <- (RX); RX <- RX + 1
			case LAX:
				readMemory(vm->memory, &memValueAtPos, vm->RX);
				vm->AC = memValueAtPos;
				vm->RX++;
			break;

			// Indexed store: (RX) <- AC; RX <- RX + 1
			case SAX:
				writeMemory(vm->memory, vm->AC, vm->RX);
				vm->RX++;
			break;

			// Direct store: RC <- (M)
			case LCD:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->RC = memValueAtPos;
			break;

			// Count and jump: RC <- RC - 1; if (RC > 0) then PC <- M
			case JCC:
				vm->RC--;
				if (vm->RC > 0) {
					vm->PC = pos;
				}
			break;

			// Call a subprogram: RX <- PC; PC <- M
			case CAL:
				vm->RX = vm->PC;
				vm->PC = pos;
			break;

			// Return to previous PC: PC <- RX
			case RET:
				vm->PC = vm->RX;
			break;

			// Load AC indirectly: AC <- ((RX)); RX <- RX + 1
			case LAI:
				readMemory(vm->memory, &memValueAtPos, vm->RX);
				readMemory(vm->memory, &memValueAtPos, memValueAtPos);
				//readMemory(vm->memory, &memValueAtPos, vm->initialPos + memValueAtPos);

				vm->AC = memValueAtPos;
				vm->RX++;
			break;

			// Store AC indirectly: ((RX)) <- AC; RX <- RX + 1 
			case SAI:
				readMemory(vm->memory, &memValueAtPos, vm->RX);
				writeMemory(vm->memory, vm->AC, memValueAtPos);
				//writeMemory(vm->memory, vm->AC, vm->RX + memValueAtPos + 1);
				
				vm->RX++;
			break;
			
			// Calculate the double of a given value: AC <- 2 * (M)
			case DOB:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm->AC = (memValueAtPos << 1); // AC = 2 * memValueAtPos
				writeMemory(vm->memory, vm->AC, pos);
			break;
			
			// Calculate the half of a given value: AC <- (M) / 2
			case MET:
				readMemory(vm->memory, &memValueAtPos, pos);
				vm-> AC = (memValueAtPos >> 1); // AC = memValueAtPos / 2
				writeMemory(vm->memory, vm->AC, pos);				
			break;
			
			// Jump on even: if AC % 2 == 0 then PC <- (M)
			case JPA:
				if (vm->AC % 2 == 0) {
					vm->PC = pos;
				}
			break;
			
			// Not a valid instruction. Exit program
			default:
				printf("Error. Unrecognized instruction.\n");
				exit(1);
			break;
		}

	} while (firstByte != HLT);

	//printMemory(vm->memory);

}
