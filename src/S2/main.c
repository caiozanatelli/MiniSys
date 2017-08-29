#include <stdlib.h>
#include <stdio.h>
#include "S2.h"

#define POS_INPUT_FILE  1
#define POS_OUTPUT_FILE 2

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Error. Incorrect parameters.\n");
		exit(1);
	}

	FILE *inputFile  = fopen(argv[POS_INPUT_FILE], "r");
	FILE *outputFile = fopen(argv[POS_OUTPUT_FILE], "w");

	if (!inputFile) {
		printf("Error. Input file could not be opened.\n");
		exit(1);
	}

	genM2Code(&inputFile, &outputFile);
	
	fclose(inputFile);
	fclose(outputFile);

	return 0;
}
