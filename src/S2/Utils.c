#include <string.h>
#include "Utils.h"

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

int isLabel(char *s) {
	return (strlen(s) == 1);
}

int isEndOfProgram(char *s) {
	return (strcmp(s, "END") == 0);
}

int isPseudoOperator(char *s) {
	return (strcmp(s, "DC") == 0 || strcmp(s, "END") == 0);
}

unsigned char getOpcode(char *instruction) {
	if (strcmp(instruction, "LAD") == 0) {
		return LAD;
	}
	else if (strcmp(instruction, "SAD") == 0) {
		return SAD;
	}
	else if (strcmp(instruction, "ADD") == 0) {
		return ADD;
	}
	else if (strcmp(instruction, "SUB") == 0) {
		return SUB;
	}
	else if (strcmp(instruction, "INP") == 0) {
		return INP;
	}
	else if (strcmp(instruction, "OUT") == 0) {
		return OUT;
	}
	else if (strcmp(instruction, "JMP") == 0) {
		return JMP;
	}
	else if (strcmp(instruction, "JGZ") == 0) {
		return JGZ;
	}
	else if (strcmp(instruction, "JLZ") == 0) {
		return JLZ;
	}
	else if (strcmp(instruction, "JZE") == 0) {
		return JZE;
	}
	else if (strcmp(instruction, "HLT") == 0) {
		return HLT;
	}
	else if (strcmp(instruction, "LXD") == 0) {
		return LXD;
	}
	else if (strcmp(instruction, "SXD") == 0) {
		return SXD;
	}
	else if (strcmp(instruction, "LAX") == 0) {
		return LAX;
	}
	else if (strcmp(instruction, "SAX") == 0) {
		return SAX;
	}
	else if (strcmp(instruction, "LCD") == 0) {
		return LCD;
	}
	else if (strcmp(instruction, "JCC") == 0) {
		return JCC;
	}

	return 0;
}
