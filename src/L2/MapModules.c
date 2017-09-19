#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "MapModules.h"

// Initialize the map for the modules
void initMap(MapModules *map) {
	map->capacity = MAP_SIZE;
	map->data = (Label*) malloc(map->capacity * sizeof(Label));
	map->size = 0;
	
	int i;
	for (i = 0; i < map->capacity; i++) {
		map->data[i].address      = EMPTY_SPOT;
		map->data[i].fileID       = EMPTY_SPOT;
	}
}

// Deallocate the memory set for the map
void freeMap(MapModules *map) {
	free(map->data);
}

// Build the modules mapping in order to link them
void buildMap(MapModules *map, Module *modules, int numModules) {
	int i;
	int isLabel;
	int label;
	int labelAddress;
	int offset;
	
	char word[15];

	modules[0].linkOffset = 0;
	
	// Read the header of each file and build the modules map
	for (i = 0; i < numModules; i++) {
		// First read the module offset which was set by the assembler (M2)
		fscanf(modules[i].fpCode, "%d", &offset);

		if (i != numModules - 1) {
			modules[i + 1].linkOffset = modules[i].linkOffset + offset;
		}

		// Process header searching for labels addresses
		isLabel = 1;		
		while (fscanf(modules[i].fpCode, "%s", word) == 1 && strcmp(word, "#") != 0) {
			if (isLabel) {
				label = getSymbolPosition(word[0]);
			}
			else {
				sscanf(word, "%d", &labelAddress);
				
				map->data[label].address = labelAddress;
				map->data[label].fileID  = i;
			}
			
			isLabel = !isLabel;
		}
	}
}

// Print the modules mapping
void printMap(MapModules *map) {
	printf("----------------------------------------------------------------------\n");
	printf(". :                           Modules Map                          : .\n\n");

	int i;	
	for (i = 0; i < MAP_SIZE; i++) {
		printf("Map[%d]: %d\t", i, map->data[i].address);
		printf("File ID: %d\n", map->data[i].fileID);
	}
	
	printf("----------------------------------------------------------------------\n");
}

// Get a valid array position for a given symbol - charset [a-zA-Z]
int getSymbolPosition(char symbol) {
	return (isupper(symbol) ? symbol - 'A' : symbol - 'a' + 26);
}

