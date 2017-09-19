#include <stdlib.h>
#include <stdio.h>
#include "Module.h"
#include "L2.h"

int main(int argc, char **argv) {
	int numModules = argc - 3;
	int i;

	// Try to open the modules to be linked
	Module modules[numModules];
	for (i = 0; i < numModules; i++) {
		initModule(&modules[i], argv[i + 1]);
	}

	// Try to open the output linked code
	FILE *outputFile = fopen(argv[argc - 2], "w");
	if (!outputFile) {
		printf("Error. The output file could not be created.\n");
		exit(1);
	}

	int loadAddress;
	sscanf(argv[argc - 1], "%d", &loadAddress);
	
	linkModules(modules, numModules, &outputFile, loadAddress);
	
	for (i = 0; i < numModules; i++) {
		freeModule(&modules[i]);
	}

	fclose(outputFile);
	
	return 0;
}
