#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "Utils.h"
#include "SymbolTable.h"

void initSymbolTable(SymbolTable *table) {
	table->capacity = TABLE_SIZE;
	table->data = (int*) malloc(table->capacity * sizeof(int));
	table->size = 0;
	
	memset(table->data, EMPTY_SPOT, table->capacity * sizeof(int));
}

void freeSymbolTable(SymbolTable *table) {
	free(table->data);
}

void printSymbolTable(SymbolTable *table) {
	printf("--------------------\n");
	printf(". : Symbol Table : .\n\n");

	int i;	
	for (i = 0; i < TABLE_SIZE; i++) {
		printf("Table[%d]: %d\n", i, table->data[i]);
	}
	
	printf("--------------------\n\n");
}

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

			table->data[symbolIndex] = ILC;
			table->size++;

			ILC += (isPseudoOperator(instruction.secondTerm)) ? 1 : 2;
		}
		else {
			ILC += (isPseudoOperator(instruction.firstTerm)) ? 1 : 2;
		}
	}
}

int getSymbolPosition(char symbol) {
	return (isupper(symbol) ? symbol - 'A' : symbol - 'a' + 26);
}

int getTableValueAt(SymbolTable *table, int index) {
	if (index < 0 || index > table->capacity) {
		printf("Error. Invalid table index.\n");
		return -1;
	}
	
	return table->data[index];
}

int getTableSize(SymbolTable *table) {
	return table->size;
}
