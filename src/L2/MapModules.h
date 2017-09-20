#ifndef MAP_MODULES_H
#define MAP_MODULES_H

#define MAP_SIZE		256
#define EMPTY_SPOT		-1
#define TRUE			1
#define FALSE			0

#include "Module.h"

typedef struct {
	int address;
	int fileID;
} Label;

typedef struct {
	Label *data;
	int capacity;
	int size;
} MapModules;

void initMap(MapModules *map);
void freeMap(MapModules *map);
void buildMap(MapModules *map, Module *modules, int numModules);
void printMap(MapModules *map);
int getSymbolPosition(char symbol);

#endif
