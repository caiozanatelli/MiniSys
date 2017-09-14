#include <stdlib.h>
#include <stdio.h>
#include "L2.h"

void linkModules(FILE *modules[], FILE **outputFile, int numModules, int initMemPos) {
	// Map the symbols in every single module
	MapModules map;
	initMap(&map);
	
	buildMap(&map, modules, numModules);
	printMap(&map);
	
	genM2LinkedCode(modules, outputFile, &map, numModules);
	
	freeMap(&map);
}

void genM2LinkedCode(FILE *modules[], FILE **out, MapModules *map, int numModules, int initMemPos) {
	int i;
	char word[15];
	
	int PC = 0;
	
	for (i = 0; i < numModules; i++) {
		rewind(modules[i]);
		while (fscanf(modules[i], "%s", word) == 1 && strcmp(word, "#") != 0) {
			// Get rid of the header
		}
		
		while (fscanf(modules[i], "%s", word) == 1) {
			
		}
	}
}


