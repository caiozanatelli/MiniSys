#ifndef M2_H
#define M2_H

#include "Memory.h"

// Macros for identifying instructions
#define LAD 1
#define SAD 2
#define ADD 3
#define SUB 4
#define INP 5
#define OUT 6
#define JMP 7
#define JGZ 8
#define JLZ 9
#define JZE 10
#define HLT 11
#define LXD 12
#define SXD 13
#define LAX 14
#define SAX 15
#define LCD 16
#define JCC 17

// Struct that defines a data type for the M2 simulator
typedef struct {
	Memory memory;
	int PC;	// Program Counter
	int AC; // Accumulator
	int RC; // Array Counter
	int RX; // Array Index
} M2;

void initM2(M2 *vm, int initMemPos);
void loadProgram(M2 *vm, char *fileDir);
void runProgram(M2 *vm);

#endif
