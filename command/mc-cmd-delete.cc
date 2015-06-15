#include "mc-cmd-delete.h"
#include <cstdio>

void mcCmdDelete::help(void){
}

mcLanguageState mcCmdDelete::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
