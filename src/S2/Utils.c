#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Utils.h"

void resetInstruction(Instruction *instruction) {
	strcpy(instruction->firstTerm, "");
	strcpy(instruction->secondTerm, "");
	strcpy(instruction->thirdTerm, "");
}

void readInstruction(Instruction *instr, char *instrLine) {
	sscanf(instrLine, "%s %s %s", instr->firstTerm, instr->secondTerm, instr->thirdTerm);
}

void printInstruction(Instruction *instruction) {
	printf("%s %s %s\n", instruction->firstTerm, instruction->secondTerm, instruction->thirdTerm);
}

int isOneByteInstruction(char *s) {
	if (isPseudoOperator(s)) {
		return TRUE;
	}

	return (strcmp(s, "SAI") == 0 || strcmp(s, "LAI") == 0 || strcmp(s, "RET") == 0 || 
			strcmp(s, "LAX") == 0 || strcmp(s, "SAX") == 0);
}

int isLabel(Instruction *instr) {
	if (strlen(instr->firstTerm) && strlen(instr->secondTerm) && strlen(instr->thirdTerm)) {
		return TRUE;
	}
	
	if (strcmp(instr->secondTerm, "SAI") == 0 || strcmp(instr->secondTerm, "LAI") == 0 ||
		strcmp(instr->secondTerm, "RET") == 0 || strcmp(instr->secondTerm, "LAX") == 0 ||
		strcmp(instr->secondTerm, "SAX") == 0) {

		return TRUE;
	}

	return FALSE;
}

int isEndOfProgram(char *s) {
	return (strcmp(s, "END") == 0);
}

int isPseudoOperator(char *s) {
	return (strcmp(s, "DC") == 0 || strcmp(s, "DA") == 0 || strcmp(s, "DS") == 0);
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
	else if (strcmp(instruction, "CAL") == 0) {
		return CAL;
	}
	else if (strcmp(instruction, "RET") == 0) {
		return RET;
	}
	else if (strcmp(instruction, "LAI") == 0) {
		return LAI;
	}
	else if (strcmp(instruction, "SAI") == 0) {
		return SAI;
	}

	return 0;
}
