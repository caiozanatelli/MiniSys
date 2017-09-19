#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Utils.h"
#include "S2.h"

// Generate M2 code from an LS2 code
void genM2Code(FILE **inputFile, FILE **outputFile) {
	// Build the symbol table (for labels) in the first pass
	SymbolTable symbolTable;
	initSymbolTable(&symbolTable);
	int offset = buildSymbolTable(&symbolTable, inputFile);
	
	// Parse the S2 instructions to M2 instructions
	buildHeader(&symbolTable, offset, outputFile);
	parseInstructions(&symbolTable, inputFile, outputFile);
	
	// Free the memory used for the symbol table
	freeSymbolTable(&symbolTable);
}

// Build the object header to help the linker later on
void buildHeader(SymbolTable *table, int offset, FILE **outputFile) {
	Label label;
	int i;

	// First, print the module offset for easier linking by the L2 module
	fprintf(*outputFile, "%d\n", offset);

	// For all labels in the symbol table, print it to the header if it's in use
	for (i = 0; i < table->capacity; i++) {
		label = getTableValueAt(table, i);
		if (isLabelUsed(&label)) {
			fprintf(*outputFile, "%c %d\n", getSymbolFromPosition(i), label.address);
		}
	}
	
	// Print the end of header identification
	fprintf(*outputFile, "#\n");
}

// Parse each of the LS2 instructions to proper M2 instructions
void parseInstructions(SymbolTable *table, FILE **inputFile, FILE **outputFile) {
	rewind(*inputFile);

	// Variables for reading the instructions from the input file
	char line[255];
	char *reader = line;

	int ILC   = 0;
	int value = 0;
	
	Instruction instruction;

	// Read the LS2 file line by line and analyse each instruction individually
	while (fscanf(*inputFile, "%[^\n]\n", reader) == 1) {
		resetInstruction(&instruction);
		readInstruction(&instruction, reader);
		//printInstruction(&instruction);

		sscanf(instruction.thirdTerm, "%d", &value);

		if (isLabel(&instruction)) {
			if (isEndOfProgram(instruction.secondTerm)) {
				break;
			}

			writeInstruction(table, outputFile, instruction.secondTerm, instruction.thirdTerm, value, &ILC);
		}
		else {
			if (isEndOfProgram(instruction.firstTerm)) {
				break;
			}

			writeInstruction(table, outputFile, instruction.firstTerm, instruction.secondTerm, value, &ILC);
		}

	}

}

void writeInstruction(SymbolTable *table, FILE **outputFile, char *firstOp, char *secondOp, int value, int *ILC) {
	char symbol = 0;
	unsigned char opCode = 0;
	unsigned int symbolLocation = 0;
	Label label;

	// It's a pseudo-instruction, so the treatment must be different
	if (isPseudoOperator(firstOp)) {
		*ILC += 1;

		// Define Constant (DC) given by the code
		if (strcmp(firstOp, "DC") == 0) {
			fprintf(*outputFile, "%d\n", value);
		}
		// Define Address (DA), that is, the absolute address of a label/parameter. 
		else if (strcmp(firstOp, "DA") == 0) {
			symbol = secondOp[0];
			label = getTableValueAt(table, getSymbolPosition(symbol));
			fprintf(*outputFile, "* %d\n", label.address);
		}
		// Define Storage (DS). Reserve an amount of memory for storage
		else if (strcmp(firstOp, "DS") == 0) {
			while (value--) {
				fprintf(*outputFile, "%d\n", 0);
			}

			*ILC += value - 1;
		}
	}
	// It's a real instruction
	else {
		*ILC += 2;
	
		opCode = getOpcode(firstOp);
		symbol = secondOp[0];
	
		// Not a valid instruction
		if (opCode == 0) {
			printf("[%s] Error. Unrecognized instruction.\n", firstOp);
			exit(1);
		}

		// The current instruction is a one-byte one, so a padding is needed
		if (opCode == HLT || opCode == LAX || opCode == SAX || opCode == LAI || opCode == SAI || opCode == RET) {
			symbolLocation = 0;
		}
		else {
			label = getTableValueAt(table, getSymbolPosition(symbol));
			symbolLocation = label.address - *ILC;
		}

		// Add subprogram reference identification for the linker
		if (opCode == CAL) {
			if (isLabelUsed(&label)) {
				fprintf(*outputFile, "! %02u\n", symbolLocation);
			}
			else {
				fprintf(*outputFile, "! %c\n", symbol);
			}
		}
		else {
			fprintf(*outputFile, "%02u %02u\n", opCode, symbolLocation);
		}
	}

}
