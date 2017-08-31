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
	buildSymbolTable(&symbolTable, inputFile);
	
	// Parse the S2 instructions to M2 instructions
	parseInstructions(&symbolTable, inputFile, outputFile);
	
	// Free the memory used for the symbol table
	freeSymbolTable(&symbolTable);
}

// Parse each of the LS2 instructions to proper M2 instructions
void parseInstructions(SymbolTable *table, FILE **inputFile, FILE **outputFile) {
	rewind(*inputFile);

	// Variables for reading the instructions from the input file
	char line[255];
	char *reader = line;

	int ILC     = 0;
	int value   = 0;
	
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

	if (isPseudoOperator(firstOp)) {
		*ILC += 1;

		if (strcmp(firstOp, "DC") == 0) {
			fprintf(*outputFile, "%d\n", value);
		}
		else if (strcmp(firstOp, "DA") == 0) {
			symbol = secondOp[0];
			fprintf(*outputFile, "%d\n", getTableValueAt(table, getSymbolPosition(symbol)) - *ILC);
		}
		else if (strcmp(firstOp, "DS") == 0) {
			printf("AQUIII PORRA\n\n");
			printf("Value %d\n\n", value);
			while (value--) {
				fprintf(*outputFile, "%d\n", 0);
			}

			*ILC += value - 1;
		}
	}
	else {
		*ILC += 2;

		opCode = getOpcode(firstOp);
		symbol = secondOp[0];

		if (opCode == 0) {
			printf("Error. Unrecognized instruction.\n");
			exit(1);
		}


		if (opCode == HLT || opCode == LAX || opCode == SAX || opCode == LAI || opCode == SAI || opCode == RET) {
			symbolLocation = 0;
		}
		else {
			symbolLocation = getTableValueAt(table, getSymbolPosition(symbol)) - *ILC;
		}

		fprintf(*outputFile, "%02u %02u\n", opCode, symbolLocation);		
	}

}
