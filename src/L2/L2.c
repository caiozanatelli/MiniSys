#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "L2.h"

// Main function called by the user to link the input modules and build a final M2 code
void linkModules(Module *modules, int numModules, FILE **outputFile, int loadAddress) {
	
	// Map the symbols in every single module
	MapModules map;
	initMap(&map);
	buildMap(&map, modules, numModules);
	
	// Generate the linked code
	genM2LinkedCode(modules, &map, numModules, outputFile, loadAddress);
	
	// Free the map structure for the modules
	freeMap(&map);
}

// After mapping the modules, this function is responsible to link them
void genM2LinkedCode(Module *modules, MapModules *map, int numModules, FILE **out, int loadAddress) {
	int i;
	char word[15];
	
	int PC = 0;
	int label = 0;
	int addr  = 0;
	
	for (i = 0; i < numModules; i++) {	

		// Process the code int order to find absolute addresses and func calls
		while (fscanf(modules[i].fpCode, "%s", word) == 1) {
			// Treatment for a subprogram call (Relative to PC)
			if (word[0] == '!') {
				PC += 2;

				if (fscanf(modules[i].fpCode, "%s", word) != 1) {
					printf("Error. Bad instruction. \n");
					exit(1);
				}
								
				label = getSymbolPosition(word[0]);

				addr = map->data[label].address;
				addr += modules[map->data[label].fileID].linkOffset - PC;

				fprintf(*out, "18 %d\n", addr);
			}
			// Treatment for absolute address
			else if (word[0] == '*') {
				PC += 1;

				if (fscanf(modules[i].fpCode, "%d", &addr) != 1) {
					printf("Error. Bad instruction. \n");
					exit(1);
				}
				
				addr += loadAddress + modules[i].linkOffset;
				fprintf(*out, "%d\n", addr);
			}
			// Treatment for a DC pseudo operator
			else if (strcmp(word, "0") == 0) {
				PC += 1;
				fprintf(*out, "%s\n", word);
			}
			// Treatment for any other type of instruction
			else {
				PC += 2;

				fprintf(*out, "%s ", word);

				if (fscanf(modules[i].fpCode, "%s", word) != 1) {
					printf("Error. Bad instruction. \n");
					exit(1);
				}

				fprintf(*out, "%s\n", word);
			}
		}
	}
}


