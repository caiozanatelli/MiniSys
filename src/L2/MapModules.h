#ifndef MAP_MODULES_H
#define MAP_MODULES_H

#define MAP_SIZE		52
#define EMPTY_SPOT		-1
#define TRUE			1
#define FALSE			0

typedef struct {
	int address;
	int fileID;
	int isAbsolute;
	int isSubprogram;
} Label;

typedef struct {
	Label *data;
	int capacity;
	int size;
} MapModules;

void initMap(MapModules *map);
void freeMap(MapModules *map);
void buildMap(MapModules *map, FILE *modules[], int numModules);
void printMap(MapModules *map);
int getSymbolPosition(char symbol);
int getSymbolIndexFromAddress(MapModules *map, int address);

#endif
