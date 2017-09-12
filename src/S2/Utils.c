#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Utils.h"
#include "SymbolTable.h"

// Reset the instruction fields
void resetInstruction(Instruction *instruction) {
	strcpy(instruction->firstTerm, "");
	strcpy(instruction->secondTerm, "");
	strcpy(instruction->thirdTerm, "");
}

// Read an instruction (there may be up to three terms)
void readInstruction(Instruction *instr, char *instrLine) {
	sscanf(instrLine, "%s %s %s", instr->firstTerm, instr->secondTerm, instr->thirdTerm);
}

// Print an instruction
void printInstruction(Instruction *instruction) {
	printf("%s %s %s\n", instruction->firstTerm, instruction->secondTerm, instruction->thirdTerm);
}

// Returns TRUE if the argument is an one-byte instruction and FALSE otherwise
int isOneByteInstruction(char *s) {
	return (strcmp(s, "SAI") == 0 || strcmp(s, "LAI") == 0 || strcmp(s, "RET") == 0 || 
			strcmp(s, "LAX") == 0 || strcmp(s, "SAX") == 0 || strcmp(s, "HLT") == 0);
}

// Returns TRUE if a given instruction is labeled and FALSE otherwise
int isLabel(Instruction *instr) {
	int lenFirstTerm  = strlen(instr->firstTerm);
	int lenSecondTerm = strlen(instr->secondTerm);
	int lenThirdTerm  = strlen(instr->thirdTerm);
	
	if (lenFirstTerm && lenSecondTerm && lenThirdTerm) {
		return TRUE;
	}
	
	return isOneByteInstruction(instr->secondTerm);
}

// Get the label type (variable or subprogram) for a given labeled instruction
int getLabelType(char *instr) {
	return (strcmp(instr, "CAL") == 0 ? ID_SUBPROGRAM : ID_VARIABLE);
}

// Returns TRUE if the pseudo-instruction END has been found and FALSE otherwise
int isEndOfProgram(char *s) {
	return (strcmp(s, "END") == 0);
}

// Returns TRUE if a pseudo-operator has been found and FALSE otherwise
int isPseudoOperator(char *s) {
	return (strcmp(s, "DC") == 0 || strcmp(s, "DA") == 0 || strcmp(s, "DS") == 0);
}

// Returns the opcode of a given instruction and 0 in case of an invalid one
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
	else if (strcmp(instruction, "DOB") == 0) {
		return DOB;
	}
	else if (strcmp(instruction, "MET") == 0) {
		return MET;
	}
	else if (strcmp(instruction, "JPA") == 0) {
		return JPA;
	}

	return 0;
}
