#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TABLE_SIZE      256
#define EMPTY_SPOT      -1
#define ID_SUBPROGRAM   0
#define ID_VARIABLE     1

// Data components of the symbol table. It contains the PC and the type of reference
typedef struct {
	int address;
	int labelType;
} Label;

// Struct that defines a symbol table type
typedef struct {
	Label *data;
	int capacity;
	int size;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
void freeSymbolTable(SymbolTable *table);
void printSymbolTable(SymbolTable *table);
int buildSymbolTable(SymbolTable *table, FILE **inputFile);
char getSymbolFromPosition(int position);
Label getTableValueAt(SymbolTable *table, int index);
int getSymbolPosition(char symbol);
int getTableSize(SymbolTable *table);
int isLabelUsed(Label *label);

#endif
