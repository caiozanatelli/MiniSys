#ifndef L2_H
#define L2_H

#include "MapModules.h"
#include "Module.h"

void linkModules(Module *modules, int numModules, FILE **outputFile, int loadAddress);
void genM2LinkedCode(Module *modules, MapModules *map, int numModules, FILE **out, int loadAddress);
//void fixAbsoluteAddresses();
//void fixReferences();

#endif
