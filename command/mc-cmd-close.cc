#include "mc-cmd-close.h"
#include <cstdio>

void mcCmdClose::help(void){
}

mcLanguageState mcCmdClose::parse(mcScanner& scanner){
	fprintf(stderr, "Not implemented\n");
	return MC_LANG_CONTINUE;
}
