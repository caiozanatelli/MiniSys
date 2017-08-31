#ifndef MEMORY_H
#define MEMORY_H

#define MAX_MEM 50
#define TRUE    1
#define FALSE   0

typedef int Word;
typedef Word Memory[MAX_MEM];

void initMemory(Memory memory);
void printMemory(Memory memory);
int writeMemory(Memory memory, Word data, int pos);
Word readMemory(Memory memory, Word *data, int pos);

#endif