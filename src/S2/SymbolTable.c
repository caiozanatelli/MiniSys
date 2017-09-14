#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "Utils.h"
#include "SymbolTable.h"

// Initialize the symbol table structure
void initSymbolTable(SymbolTable *table) {
	table->capacity = TABLE_SIZE;
	table->data = (Label*) malloc(table->capacity * sizeof(Label));
	table->size = 0;
	
	int i;
	for (i = 0; i < table->capacity; i++) {
		table->data[i].address   = EMPTY_SPOT;
		table->data[i].labelType = EMPTY_SPOT;
	}
}

// Deallocate the symbol table
void freeSymbolTable(SymbolTable *table) {
	free(table->data);
}

// Print the symbol table contents
void printSymbolTable(SymbolTable *table) {
	printf("--------------------\n");
	printf(". : Symbol Table : .\n\n");

	int i;	
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("Table[%d]: %d", i, table->data[i].address);
		printf("%s\n", (table->data[i].labelType == ID_SUBPROGRAM) ? "SUB_PROGRAM" : "VARIABLE");
	}
	
	printf("--------------------\n\n");
}

// Build the symbol table based on the LS2 code given by input
void buildSymbolTable(SymbolTable *table, FILE **inputFile) {
	char line[255];
	char *reader = line;
	
	Instruction instruction;
	
	int ILC = 0;
		
	while (fscanf(*inputFile, "%[^\n]\n", reader) == 1) {
		resetInstruction(&instruction);
		readInstruction(&instruction, reader);
		
		if (isLabel(&instruction)) {
			int symbolIndex = getSymbolPosition(instruction.firstTerm[0]);
			
			//table->size += (getTableValueAt(table, symbolIndex) == -EMPTY_SPOT);

			table->data[symbolIndex].address   = ILC;
			table->data[symbolIndex].labelType = getLabelType(instruction.secondTerm);
			table->size++;

			ILC += (isPseudoOperator(instruction.secondTerm)) ? 1 : 2;
		}
		else {
			ILC += (isPseudoOperator(instruction.firstTerm)) ? 1 : 2;
		}
	}
}

// Get a valid array position for a given symbol - charset [a-zA-Z]
int getSymbolPosition(char symbol) {
	return (isupper(symbol) ? symbol - 'A' : symbol - 'a' + 26);
}

// Get a char symbol for its integer valid position representation
char getSymbolFromPosition(int position) {
	return (position <= 25 ? position + 'A' : position + 'a');
}

// Get the content for a given position at the symbol table
Label getTableValueAt(SymbolTable *table, int index) {
	if (index < 0 || index > table->capacity) {
		printf("Error. Invalid table index.\n");
		exit(1);
	}
	
	return table->data[index];
}

// Get the number of labels present in the table
int getTableSize(SymbolTable *table) {
	return table->size;
}

// Verify if a label is being used in the code
int isLabelUsed(Label *label) {
	return (label->address != EMPTY_SPOT && label->labelType != EMPTY_SPOT);
}
