#ifndef UTILS_H
#define UTILS_H

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
#define CAL 18
#define RET 19
#define LAI 20
#define SAI 21
#define DOB 22
#define MET 23
#define JPA 24

#define OPERAND_SIZE 10

#define TRUE  1
#define FALSE 0

// Definition of a data type that contains all of the three possible terms of an instruction
typedef struct {
	char firstTerm[OPERAND_SIZE];
	char secondTerm[OPERAND_SIZE];
	char thirdTerm[OPERAND_SIZE];
} Instruction;

void resetInstruction(Instruction *instruction);
void readInstruction(Instruction *instruction, char *instructionLine);
void printInstruction(Instruction *instruction);

int isLabel(Instruction *instruction);
int getLabelType(char *instr);
int isOneByteInstruction(char *s);
int isEndOfProgram(char *s);
int isPseudoOperator(char *s);
unsigned char getOpcode(char *instruction);

#endif
