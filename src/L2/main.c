#include <stdlib.h>
#include <stdio.h>
#include "L2.h"

int main(int argc, char **argv) {
	int numModules = argc - 2;
	
	FILE *modules[numModules];
	
	int i;
	for (i = 0; i < numModules; i++) {
		modules[i] = fopen(argv[i + 1], "r");
		if (!modules[i]) {
			printf("Error. The module %s could not be opened.\n", argv[i]);
			exit(1);
		}
	}
	
	FILE *outputFile = fopen(argv[argc - 1], "w");
	if (!outputFile) {
		printf("Error. The output file could not be created.\n");
		exit(1);
	}
	
	linkModules(modules, &outputFile, numModules);
	
	for (i = 0; i < numModules; i++) {
		fclose(modules[i]);
	}
	
	fclose(outputFile);
	
	return 0;
}
