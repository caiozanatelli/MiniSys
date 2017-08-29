#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TABLE_SIZE	52
#define EMPTY_SPOT	-1

typedef struct {
	int *data;
	int capacity;
	int size;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
void freeSymbolTable(SymbolTable *table);
void printSymbolTable(SymbolTable *table);
void buildSymbolTable(SymbolTable *table, FILE **inputFile);
int getSymbolPosition(char symbol);
int getTableValueAt(SymbolTable *table, int index);
int getTableSize(SymbolTable *table);

#endif
