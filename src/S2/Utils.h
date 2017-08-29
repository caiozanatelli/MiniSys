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

int isLabel(char *s);
int isEndOfProgram(char *s);
int isPseudoOperator(char *s);
unsigned char getOpcode(char *instruction);

#endif
