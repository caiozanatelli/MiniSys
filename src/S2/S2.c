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
	
	// Parse the LS2 instructions to M2 instructions
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
	char firstTerm[5];
	int value;
	
	int ILC = 0;

	// Read the LS2 file line by line and analyse each instruction individually
	while (fscanf(*inputFile, "%[^\n]\n", reader) == 1) {
		ILC += 2;
		
		// Read the first term of the instruction (it can be a label or an operation)
		sscanf(reader, "%s", firstTerm);
		reader = &reader[strlen(firstTerm) + 1];
	
		// If the first term is not a label		
		if (!isLabel(firstTerm)) {
			if (isEndOfProgram(firstTerm)) {
				break;
			}
			
			// Get the rest of the instruction and write it in the output file
			writeInstruction(table, outputFile, reader, firstTerm, ILC);
		}
		else {
			sscanf(reader, "%s", firstTerm);
			reader = &reader[strlen(firstTerm) + 1];
			
			if (isEndOfProgram(firstTerm)) {
				break;
			}
			
			if (isPseudoOperator(firstTerm)) {
				sscanf(reader, "%d", &value);
				fprintf(*outputFile, "%d\n", value);
				continue;
			}
			else {
				writeInstruction(table, outputFile, reader, firstTerm, ILC);
			}
		}
	}

}

void writeInstruction(SymbolTable *table, FILE **outputFile, char *reader, char *instruction, int ILC) {
	char symbol;
	sscanf(reader, "%c", &symbol);
	
	int symbolLocation = getTableValueAt(table, getSymbolPosition(symbol)) - ILC;
	unsigned char opCode = getOpcode(instruction);

	if (opCode == 11) { 
		symbolLocation = 0;
	}
	else if (opCode == 0) {
		printf("Error. Unrecognized instruction.\n");
		exit(1);
	}

	fprintf(*outputFile, "%02u %02u\n", opCode, symbolLocation);
}
