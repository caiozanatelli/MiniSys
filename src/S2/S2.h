#ifndef S2_H
#define S2_H

#include "SymbolTable.h"

void genM2Code(FILE **inputFile, FILE **outputFile);
void buildHeader(SymbolTable *table, FILE **outputFile);
void parseInstructions(SymbolTable *table, FILE **inputFile, FILE **outputFile);
void writeInstruction(SymbolTable *table, FILE **outputFile, char *firstOp, char *secondOp, int value, int *ILC);

#endif
