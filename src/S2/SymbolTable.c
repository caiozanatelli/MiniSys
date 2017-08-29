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
	char firstTerm[5];
	char firstOperator[5];
	
	int ILC = 0;
		
	while (fscanf(*inputFile, "%[^\n]\n", reader) == 1) {
		sscanf(reader, "%s", firstTerm);
		reader = &reader[strlen(firstTerm) + 1];
		
		if (isLabel(firstTerm)) {
			sscanf(reader, "%s", firstOperator);
			reader = &reader[strlen(firstOperator) + 1];
			
			int symbolIndex = getSymbolPosition(firstTerm[0]);
			
			//table->size += (getTableValueAt(table, symbolIndex) == -EMPTY_SPOT);

			table->data[symbolIndex] = ILC;
			table->size++;
			
			if (isPseudoOperator(firstOperator)) {
				ILC++;
				continue;
			}
		}
		
		ILC += 2;
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
