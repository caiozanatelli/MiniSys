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
		map->data[i].isAbsolute   = EMPTY_SPOT;
		map->data[i].isSubprogram = EMPTY_SPOT;
	}
}

// Deallocate the memory set for the map
void freeMap(MapModules *map) {
	free(map->data);
}

// Build the modules mapping in order to link them
void buildMap(MapModules *map, FILE *modules[], int numModules) {
	int i;
	int isLabel;
	int label;
	int labelAddress;
	int absoluteAddr;
	
	char word[15];
	
	// Read the header of each file and build the modules map
	for (i = 0; i < numModules; i++) {
		isLabel = 1;		
		
		// Process header searching for labels addresses
		while (fscanf(modules[i], "%s", word) == 1 && strcmp(word, "#") != 0) {
			if (isLabel) {
				label = getSymbolPosition(word[0]);
			}
			else {
				sscanf(word, "%d", &labelAddress);
				
				map->data[label].address = labelAddress;
				map->data[label].fileID  = i;
				//map->data[label].isSubprogram = 0;
				//map->data[label].isAbsolute = 0;
			}
			
			isLabel = !isLabel;
		}
		
		// Process the code int order to find absolute addresses and func calls
		while (fscanf(modules[i], "%s", word) == 1) {
			if (word[0] == '!') { // This is a call to a subprogram
				if (fscanf(modules[i], "%s", word) != 1) {
					continue;
				}
								
				label = getSymbolPosition(word[0]);
				map->data[label].isSubprogram = TRUE;
				map->data[label].isAbsolute   = FALSE;
			}
			else if (word[0] == '*') {
				if (fscanf(modules[i], "%d", &absoluteAddr) != 1) {
					continue;
				}
				
				label = getSymbolIndexFromAddress(map, absoluteAddr);
				
				if (label < 0) {
					printf("Error. Absolute addres not valid.\n");
					exit(1);
				}
				
				map->data[label].isSubprogram = FALSE;
				map->data[label].isAbsolute   = TRUE;
			}
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
		printf("File ID: %d\tAbsolute Addr: %d", map->data[i].fileID, map->data[i].isAbsolute);
		printf("\tSubprogram: %d\n", map->data[i].isSubprogram);
	}
	
	printf("----------------------------------------------------------------------\n");
}

// Get a valid array position for a given symbol - charset [a-zA-Z]
int getSymbolPosition(char symbol) {
	return (isupper(symbol) ? symbol - 'A' : symbol - 'a' + 26);
}

int getSymbolIndexFromAddress(MapModules *map, int address) {
	int i;
	for (i = 0; i < map->capacity; i++) {
		if (map->data[i].address == address) {
			return i; 
		}
	}
	
	return -1;
}

