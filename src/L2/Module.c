#include <stdlib.h>
#include <stdio.h>
#include "Module.h"

// Initialize each module (M2 object code) by opening its file
void initModule(Module *module, char *dirModule) {
	module->linkOffset = 0;
	module->fpCode = fopen(dirModule, "r");
	if (!module->fpCode) {
		printf("Error. The module %s could not be opened.\n", dirModule);
		exit(1);
	}
}

// Free all the modules opened
void freeModule(Module *module) {
	fclose(module->fpCode);	
}

// Set an offset value to a module
void setModuleOffset(Module *module, int offset) {
	module->linkOffset = offset;
}

// Get the offset value of a module
int getModuleOffset(Module *module) {
	return module->linkOffset;
}

