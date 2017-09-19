#ifndef MODULE_H
#define MODULE_H

typedef struct {
	FILE *fpCode;
	int linkOffset;
} Module;

void initModule(Module *modules, char *dirModule);
void freeModule(Module *module);
void setModuleOffset(Module *module, int offset);
int getModuleOffset(Module *module);

#endif
